
class GamesController < ApplicationController
	before_action :authenticate_user!

	def index
		@games = Game.all
	end

	def to_spectate
		@games = Game.where(status: :started).or(Game.where(status: :paused))
	end

	def show
		@game = Game.find_by_id(params[:id])

		if (!@game)
			return head :not_found
		end

		if (!@current_user.is_playing_in?(@game) && !@current_user.is_spectating?(@game))
				@current_user.add_role(:spectator, @game);
		end
        @game
    end

	def createFriendly
		if current_user.inGame? || current_user.pendingGame
			return render json: {"you" => ["already have a game started or pending"]}, status: :unprocessable_entity
		end
		@games = Game.where(status: :pending)

		@games.to_ary.each do | game |
			if game.goal == params[:goal].to_i && game.level == params[:level] && game.game_type == params[:game_type]
				@game = game
				@game.launch_friendly(@current_user)
				return @game
			end
		end
		@game = Game.create(game_params)
        if @game.save
			ExpireGameJob.set(wait_until: DateTime.now + 5.minutes).perform_later(@game, nil)
			@game.add_host(current_user)
			@game
        else
            render json: @game.errors, status: :unprocessable_entity
		end
	end

	def cancelFriendly
		@game = Game.find_by_id(params[:id])

		if (!@game || !@game.pending?)
			return render json: {"you" => ["have no pending game"]}, status: :not_found
		else
			@game.destroy
		end
	end

	def ready
		@game = Game.find_by_id(params[:id])

		if (!@game)
			return render json: {"game" => ["doesn't exist"]}, status: :not_found
		elsif (!@game.matched?)
			return render json: {"game" => ["has expired"]}, status: :unprocessable_entity
		end

		player = @game.game_users.where(user_id: params[:user_id]).first

		if (!player)
			return render json: {"you" => ["are not a player in this game"]}, status: :unprocessable_entity
		elsif (@current_user.id != player.user_id)
			return render json: {"you" => ["can't start an other player game"]}, status: :unprocessable_entity
		end

		player.update(status: :ready);

		@game.broadcast({"action" => "player_ready", "playerId": player.user_id})

		if (@game.game_users.accepted.size == 0)
			@game.update(status: :started)
			@game.broadcast({"action" => "started"})
			ActionCable.server.broadcast("games_to_spectate", {"event" => "new_game", "game" => @game.to_spectate_json});
		end

		@game
	end

	def giveUp
		@game = Game.find_by_id(params[:id])

		if (!@game)
			return render json: {"game" => ["doesn't exist"]}, status: :not_found
		elsif (@game.finished?)
			return render json: {"game" => ["is already finished"]}, status: :unprocessable_entity
		elsif (@game.pending? || @game.matched?)
			return render json: {"game" => ["has not started yet"]}, status: :unprocessable_entity
		end

		player = @game.game_users.where(user_id: params[:user_id]).first

		if (!player)
			return render json: {"you" => ["are not a player in this game"]}, status: :unprocessable_entity
		elsif (@current_user.id != player.user_id)
			return render json: {"you" => ["can't give up an other player game"]}, status: :unprocessable_entity
		end

		@game.give_up(player)

		@game
	end

	def challengeWT
		@warTime = WarTime.find_by_id(params[:warTimeId])
		@war = @warTime.war
		@guild = Guild.find_by_id(current_user.guild.id)
		@opponent = @war.opponent(@guild)

		if not @guild.atWar? || @opponent.atWar? || @war.atWarTime?
			render json: {"War" => ["inexistent or war time is inactive"]}, status: :unprocessable_entity
			return
		end
		if @warTime.activeGame || @warTime.pendingGame
			render json: {"There" => ["is already a pending or started game in this war time"]}, status: :unprocessable_entity
			return
		end

		if current_user.inGame? || current_user.pendingGame || current_user.matchedGame
			render json: {"You" => ["already have a Game started or pending"]}, status: :unprocessable_entity
			return
		end

		@game = Game.create(game_params)

		if @game.save
			@game.update(war_time: @warTime)
			@game.add_host(current_user)
			@guild.members.each do |member|
				if not member == current_user
					member.send_notification("#{current_user.name} from your Guild has challenged #{@opponent.name} to a War Time match!", "/wars", "war")
				end
			end
			@opponent.members.each do |member|
				member.send_notification("#{current_user.name} has challenged your Guild to a War Time match! Answer the call!", "/wars", "war")
			end
			ExpireWarTimeGameJob.set(wait_until: DateTime.now + @war.time_to_answer.minutes).perform_later(@game, @guild, @opponent, @warTime, current_user)
			@game
		else
			render json: @game.errors, status: :unprocessable_entity
		end
	end

	def acceptChallengeWT
		@game = Game.find_by_id(params[:id])
		@warTime = @game.war_time
		@war = @warTime.war
		@guild = Guild.find_by_id(current_user.guild.id)
		@opponent = @war.opponent(@guild)

		if not @guild.atWar? || @opponent.atWar? || @war.atWarTime?
			render json: {"War" => ["inexistent or war time is inactive"]}, status: :unprocessable_entity
			return
		end
		if @warTime.activeGame
			render json: {"There" => ["is already a started game in this war time"]}, status: :unprocessable_entity
			return
		end

		if current_user.inGame? || current_user.pendingGame || current_user.matchedGame
			render json: {"You" => ["already have a Game started or pending"]}, status: :unprocessable_entity
			return
		end

		@game.update(status: :matched)
		@game.add_second_player(current_user)

		@guild.members.each do |member|
			if not member == current_user
				member.send_notification("#{current_user.name} from your Guild has accepted a War Time challenge against #{@opponent.name}. Click to watch the game!", "/game/#{@game.id}", "war")
			end
		end
		@opponent.members.each do |member|
			member.send_notification("#{current_user.name} has accepted your Guild's War Time challenge. Click to watch the game!", "/game/#{@game.id}", "war")
		end
		ExpireMatchedGameJob.set(wait: 2.minutes).perform_later(@game)
		@game
	end

	def playChat
		if current_user.inGame? || current_user.pendingGame || current_user.matchedGame
			render json: {"You" => ["already have a Game started or pending"]}, status: :unprocessable_entity
			return
		end

		@room = Room.find_by_id(params[:room_id])
		@room.room_messages.each do |msg|
			if msg.game.present?
				if msg.game.pending?
					render json: {"Game" => ["already pending"]}, status: :unprocessable_entity
					return
				end
			end
		end

		@game = Game.create(game_params)
		if @game.save
			@game.update(game_type: :chat)
			@game.add_host(current_user)
			ExpireGameJob.set(wait_until: DateTime.now + 5.minutes).perform_later(@game, @room)
			@game
		else
			render json: @game.errors, status: :unprocessable_entity
		end
	end

	def acceptPlayChat
		if current_user.inGame? || current_user.pendingGame || current_user.matchedGame
			render json: {"You" => ["already have a Game started or pending"]}, status: :unprocessable_entity
			return
		end

		@game = Game.find_by_id(params[:id])
		if not @game.pending?
			return render json: {"game" => ["is not pending"]}, status: :unprocessable_entity
		end
		@game.launch_friendly(@current_user)
		@game
	end

	def ladderChallenge
		if current_user.inGame? || current_user.pendingGame || current_user.pendingGameToAccept || current_user.matchedGame
			render json: {"You" => ["already have a Game started or pending"]}, status: :unprocessable_entity
			return
		end
		@opponent = User.find_by_id(params[:opponent_id])
		if @opponent.inGame? || @opponent.pendingGame || @opponent.pendingGameToAccept || @opponent.matchedGame
			render json: {"Opponent" => ["already has a Game started or pending"]}, status: :unprocessable_entity
			return
		end

		if current_user.ladder_unchallengeable == @opponent.id
            render json: {"You" => ["just lost to this user"]}, status: :unprocessable_entity
            return
        end

		if current_user.ladder_rank < @opponent.ladder_rank
			render json: {"This" => [" user must have moved down the ladder while you were choosing. Please refresh to choose an opponent that is ranked higher than you. "]}, status: :unprocessable_entity
			return
		end

		@game = Game.create(level: :normal, goal: 9, game_type: :ladder, status: :pending)
		@game.add_host(current_user)
		@game.users.push(@opponent)
		@opponent.game_users.where(game: @game).first.update(status: :pending)
		@opponent.send_notification("#{current_user.name} has challenged you to a Ladder Game", "/tournaments/ladder", "game")
		ExpireGameJob.set(wait_until: DateTime.now + 5.minutes).perform_later(@game, nil)
		@game
	end

	def acceptLadderChallenge
		if current_user.inGame? || current_user.pendingGame || current_user.matchedGame
			render json: {"You" => ["already have a Game started or pending"]}, status: :unprocessable_entity
			return
		end
		@game = Game.find_by_id(params[:id])
		if not @game.pending?
			return render json: {"game" => ["is not pending"]}, status: :unprocessable_entity
		end
		current_user.game_users.where(game: @game).first.update(status: :accepted)
		@game.update(status: :matched)
		@game.add_player_role(current_user)
		@game.broadcast({"action" => "matched"})
		ExpireMatchedGameJob.set(wait: 2.minutes).perform_later(@game)
		@game
	end

	def startTournamentGame
		@game = Game.find_by_id(params[:id])
		@opponent = @game.opponent(current_user)
		@tournament = Tournament.find_by_id(@game.tournament_id)

		if current_user.inGame? || (current_user.pendingGame && current_user.pendingGame.id != @game.id) || current_user.pendingGameToAccept
			render json: {"You" => ["already have a Game started or pending"]}, status: :unprocessable_entity
			return
		end

		if not @game.pending?
			render json: {"Game" => ["is already started or over."]}, status: :unprocessable_entity
			return
		end
		player = @game.game_users.where(user_id: current_user.id).first
		player.update(status: :accepted)

		if (@game.game_users.pending.size == 0)
			@game.add_player_role(current_user)
			@game.update(status: :matched)
			@game.broadcast({"action" => "matched"})
			ExpireTourMatchedGameJob.set(wait: 2.minutes).perform_later(@game, @tournament)
		else
			current_user.remove_role(:spectator, @game);
			current_user.add_role(:host, @game);
			@opponent.send_notification("#{current_user.name} wants to play your tournament game", "/tournaments/temporary", "tournament")
		end
		@game
	end

	private
    def game_params
        params.permit(:level, :goal, :game_type)
	end
end
