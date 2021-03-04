json.players do
	json.array! game.users.sort_by {|u| u.id === @current_user.id ? -1 : 1} do |user|
	   json.extract! user, :id, :name
	   json.avatar_url url_for(user.avatar) if user.avatar.attached?
	   json.points user.game_points(game)
	   json.status user.game_status(game)
	end
end
