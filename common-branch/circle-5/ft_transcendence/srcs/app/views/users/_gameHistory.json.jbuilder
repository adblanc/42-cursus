json.partial! "users/user", user: user
if user.games_finished
	json.games do
		json.array! user.games_finished.sort_by{|g| g[:created_at]}.reverse! do |game|
			json.id game.id
			json.status game.status
			json.created_at game.created_at
			json.game_type game.game_type
			json.level game.level
			json.won user.game_won?(game)
			json.partial! "games/gamePlayers", game: game
			json.goal game.goal
			json.created_at game.created_at
		end
	end
else
	json.games nil
end
