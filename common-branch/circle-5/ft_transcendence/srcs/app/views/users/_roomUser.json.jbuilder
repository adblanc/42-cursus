json.partial! "users/user", user: user
json.roomRole user.room_role(room)
json.isRoomAdministrator user.is_room_administrator?(room)
json.isMute user.is_room_mute?(room)
json.isBan user.is_room_ban?(room)
json.isBlocked @current_user.is_blocked?(user)
json.inGame user.inGame?
if user.pendingGame
	json.pendingGame do
		json.id user.pendingGame.id
		json.game_type user.pendingGame.game_type
		json.goal user.pendingGame.goal
		json.level user.pendingGame.level
		json.status user.pendingGame.status
		json.war_time user.pendingGame.war_time
	end
else
	json.pendingGame nil
end
