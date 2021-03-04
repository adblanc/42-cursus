json.array! @rooms do |room|
	json.partial! "rooms/room", room: room
end
