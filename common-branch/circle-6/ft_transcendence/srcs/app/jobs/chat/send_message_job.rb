class SendMessageJob < ApplicationJob
	queue_as :default

	def perform(user, room, content, game)
	  # Do something later
	  msg = RoomMessage.create(user: user, room: room, content: content, game: game)

	  ActionCable.server.broadcast("room_#{room.id}", {"message" => msg});
	end
  end
