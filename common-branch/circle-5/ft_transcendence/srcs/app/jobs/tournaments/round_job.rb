class RoundJob < ApplicationJob
	queue_as :default

	def perform(tournament)
		return if tournament.finished?
	  handle_games(tournament)

	  if tournament.quarter? || tournament.semi?
		change_round(tournament)
	  	RoundJob.set(wait_until: DateTime.now + 5.minutes).perform_later(tournament)
	  end
	end

	private

	def change_round(tournament)
		if tournament.quarter?
			tournament.update(status: :semi)
			ActionCable.server.broadcast("tournament_#{tournament.id}", {})
		else
			tournament.update(status: :final)
			ActionCable.server.broadcast("tournament_#{tournament.id}", {})
		end
		tournament.games.where(tournament_round: tournament.status).each do | game |
			game.update(status: :pending)
		end
		tournament.tournament_users.competing.each do | t_user |
		  t_user.user.send_notification("#{tournament.name} : #{tournament.status} games are up!", "tournaments/#{tournament.id}", "tournaments")
		end
	end

	def handle_games(tournament)
		tournament.games.where(tournament_round: tournament.status).each do | game |
			if game.matched? || game.started? || game.paused?
				handle_running_games(tournament, game)
			elsif game.pending? && game.game_users.where(status: :accepted).first.present?
				@winner = game.game_users.where(status: :accepted).first.user
				tournament.finish_game(@winner, game)
				tournament.forfeit_notif(game.winner, game.loser, true)
			elsif game.pending? && game.final?
				game.update(status: :abandon)
				game.users.each do | user |
					user.game_users.where(game: game).first.update(status: :lose)
					user.tournament_users.where(tournament: tournament).first.update(status: :eliminated)
					user.send_notification("You haven't played your tournament final. You have lost the tournament!", "tournaments/#{tournament.id}", "tournaments")
				end
				tournament.finish_tournament(nil)
			elsif game.pending?
				@random = game.users.sample
				tournament.finish_game(@random, game)
				tournament.forfeit_notif(game.winner, game.loser, false)
			end
		end
	end

	def handle_running_games(tournament, game)
		if game.matched?
			if game.game_users.where(status: :ready).first.present?
				@winner = game.game_users.where(status: :ready).first.user
				tournament.finish_game(@winner, game)
				@gu_win = game.game_users.where(user_id: @winner.id).first
				@gu_lose = game.game_users.where.not(user_id: @winner.id).first
				game.broadcast({"action" => "round_stop"});
				game.broadcast_end(@gu_win, @gu_lose)
				tournament.forfeit_notif(game.winner, game.loser, true)
			elsif game.final?
				game.update(status: :abandon)
				game.users.each do | user |
					user.game_users.where(game: game).first.update(status: :lose)
					user.tournament_users.where(tournament: tournament).first.update(status: :eliminated)
					user.send_notification("You haven't played your tournament final. You have lost the tournament!", "tournaments/#{tournament.id}", "tournaments")
				end
				game.broadcast({"action" => "round_stop"});
				game.broadcast_end(nil, nil)
				tournament.finish_tournament(nil)
			else
				@random = game.users.sample
				tournament.finish_game(@random, game)
				@gu_win = game.game_users.where(user_id: @random.id).first
				@gu_lose = game.game_users.where.not(user_id: @random.id).first
				game.broadcast({"action" => "round_stop"});
				game.broadcast_end(@gu_win, @gu_lose)
				tournament.forfeit_notif(game.winner, game.loser, false)
			end
		elsif game.started? || game.paused?
			@points = 0
			@winner = game.users.sample
			@forfeit = true
			game.game_users.each do |gu|
				if gu.points > @points
					@winner = gu.user
					@points = gu.points
					@forfeit = false
				end
			end
			if @forfeit
				tournament.finish_game(@winner, game)
				tournament.forfeit_notif(game.winner, game.loser, false)
			else
				tournament.finish_game_without_forfeit(@winner, game)
			end
			@gu_win = game.game_users.where(user_id: @winner.id).first
			@gu_lose = game.game_users.where.not(user_id: @winner.id).first
			game.broadcast({"action" => "round_stop"});
			game.broadcast_end(@gu_win, @gu_lose)
		end
	end

end
