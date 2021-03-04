class ExpireMatchedGameJob < ApplicationJob
	queue_as :default

	def perform(game)
	  return unless game.matched?

		winner = game.game_users.where(status: :ready).first
		if winner
			winner.update(status: :won)
			looser = game.game_users.where.not(id: winner.id).first
			if (looser)
				looser.update(status: :lose)
			end
			game.update(status: :forfeit)
			game.handle_end_cases
			game.broadcast_end(winner, looser)
		else
			if game.room_message.present?
				game.update(status: :chat_expired)
				game.broadcast_end(nil, nil)
				return
			else
				game.update(status: :forfeit)
				game.broadcast_end(nil, nil)
				queue = Sidekiq::ScheduledSet.new
				queue.each do |job|
					if job.args.first["arguments"].first["_aj_globalid"] == "gid://active-storage/Game/#{game.id}"
						job.delete
					end
				end
				game.destroy
			end
		end
	end
end
