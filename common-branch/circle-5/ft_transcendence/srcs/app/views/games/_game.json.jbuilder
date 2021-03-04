json.extract! game, :id, :level, :goal, :status, :game_type, :war_time, :created_at
json.isSpectator @current_user.is_spectating?(game)
json.isHost @current_user.is_host?(game)

json.spectators do
	json.array! game.spectators do |spectator|
		json.partial! "games/spectator", spectator: spectator
	end
end
json.partial! "games/gamePlayers", game: game

opponent = game.game_user_opponent(@current_user)
if (opponent)
	json.extract! opponent, :pause_duration, :last_pause
end
