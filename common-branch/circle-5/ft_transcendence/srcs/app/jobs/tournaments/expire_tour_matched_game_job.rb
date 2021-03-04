class ExpireTourMatchedGameJob < ApplicationJob
	queue_as :default

	def perform(game, tournament)
	  return unless game.matched?

	  if game.game_users.where(status: :ready).first.present?
		@winner = game.game_users.where(status: :ready).first.user
		tournament.finish_game(@winner, game)
		@gu_win = game.game_users.where(user_id: @winner.id).first
		@gu_lose = game.game_users.where.not(user_id: @winner.id).first
		game.broadcast_end(@gu_win, @gu_lose)
		tournament.forfeit_notif(game.winner, game.loser, true)
	  elsif game.final?
		game.update(status: :abandon)
		game.users.each do | user |
			user.game_users.where(game: game).first.update(status: :lose)
			user.tournament_users.where(tournament: tournament).first.update(status: :eliminated)
			user.send_notification("You haven't played your tournament final. You have lost the tournament!", "tournaments/#{tournament.id}", "tournaments")
		end
		game.broadcast_end(nil, nil)
		tournament.finish_tournament(nil)
	  else
		@random = game.users.sample
		tournament.finish_game(@random, game)
		@gu_win = game.game_users.where(user_id: @random.id).first
		@gu_lose = game.game_users.where.not(user_id: @random.id).first
		game.broadcast_end(@gu_win, @gu_lose)
		tournament.forfeit_notif(game.winner, game.loser, false)
	  end
	end
end
