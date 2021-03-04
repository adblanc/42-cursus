class RoomMessagesController < ApplicationController
	before_action :authenticate_user!
	before_action :load_entities
	before_action :load_game

	def create
		if (!@room)
			render json: {"room" => ["not found"]}, status: :unprocessable_entity
		elsif (!@current_user.rooms.exists?(@room.id))
			render json: {"you" => ["are not in this room"]}, status: :unprocessable_entity
		elsif (@current_user.is_room_mute?(@room))
			render json: {"you" => ["are mute in this room"]}, status: :unprocessable_entity
		elsif (@current_user.is_room_ban?(@room))
			render json: {"you" => ["are ban in this room"]}, status: :unprocessable_entity
		else
			if @game
				SendMessageJob.perform_now(current_user, @room, params[:content], @game)
			else
				SendMessageJob.perform_now(current_user, @room, params[:content], nil)
			end
		end
	end

	protected

  def load_entities
    @room = Room.find_by_id(params[:room_id])
  end
  def load_game
	if params[:game_id]
		@game = Game.find_by_id(params[:game_id])
	end
  end
end
