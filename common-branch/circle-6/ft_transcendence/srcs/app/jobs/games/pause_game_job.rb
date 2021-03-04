class PauseGameJob < ApplicationJob
	queue_as :default

	def perform(game_id, player_id)
		game = Game.find_by_id(game_id)
		player = GameUser.find_by_id(player_id)

		if game.started? || game.finished? || game.forfeit? || game.abandon? || game.chat_expired? || !player
			return
	  	end

		@winner = game.game_users.where.not(user_id: player.user_id).first
		@loser = player
		@winner.update(status: :won)
		@loser.update(status: :lose)
	  	game.update(status: :forfeit)
		game.handle_end_cases
		game.broadcast_end(@winner, @loser);
	end
end
