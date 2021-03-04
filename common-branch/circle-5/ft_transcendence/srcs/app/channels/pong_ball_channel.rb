class PongBallChannel < ApplicationCable::Channel
	def subscribed
		@id = params[:id]
		@game = Game.find_by_id(@id)

		reject unless @game

		stream_from "pong_ball_#{@id}"
	end

	def movement(data)
	   if (current_user.is_host?(@game))
		ActionCable.server.broadcast("pong_ball_#{@id}", data);
	   end
	end

	def unsubscribed
	end
  end
