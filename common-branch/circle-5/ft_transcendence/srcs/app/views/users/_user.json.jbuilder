json.extract! user, :id, :login, :email, :two_fact_auth, :name, :contribution, :appearing_on, :created_at, :updated_at
json.is_present user == @current_user ? true : user.is_present
json.inGame user.appearing_on == "in game"
json.is_friend @current_user.is_friend_of?(user);
json.avatar_url url_for(user.avatar) if user.avatar.attached?
json.ladder_rank user.ladder_rank
json.ladder_unchallengeable user.ladder_unchallengeable
json.inGame user.inGame?
json.guild_role user.guild_role?
json.admin user.admin?
json.master user.master?
json.ban user.is_banned?
json.ban_time user.ban_time
if user.guild_role?
	json.guild do
		json.partial! "guilds/guild", guild: user.guild
	end
else
	json.guild nil
end
if user.pending_guild?
  json.pending_guild do
		json.id user.pending_guild.id
		json.name user.pending_guild.name
		json.points user.pending_guild.points
		json.img_url url_for(user.pending_guild.img) if user.pending_guild.img.attached?
	end
else
	json.pending_guild nil
end

if user.matchedGame
	json.matchedGame user.matchedGame
else
	json.matchedGame nil
end

if user.currentGame
	json.currentGame user.currentGame
else
	json.currentGame nil
end


if user.tournamentToPlay
	json.tournamentToPlay user.tournamentToPlay
else
	json.tournamentToPlay nil
end

if user.pendingGame
	json.pendingGame do
		json.id user.pendingGame.id
		json.game_type user.pendingGame.game_type
		json.goal user.pendingGame.goal
		json.level user.pendingGame.level
		json.war_time user.pendingGame.war_time
		if user.pendingGame.opponent(user)
			json.opponent do
				json.partial! "users/userSnippet", user: user.pendingGame.opponent(user)
			end
		end
	end
else
	json.pendingGame nil
end

if user.pendingGameToAccept
	json.pendingGameToAccept do
		json.id user.pendingGameToAccept.id
		json.game_type user.pendingGameToAccept.game_type
		json.goal user.pendingGameToAccept.goal
		json.level user.pendingGameToAccept.level
		json.opponent do
			json.partial! "users/userSnippet", user: user.pendingGameToAccept.opponent(user)
		end
	end
else
	json.pendingGameToAccept nil
end

json.friends do
	json.array! user.friends do |friend|
		json.partial! "users/userSnippet", user: friend
	end
end

if user.friend_requests_as_receiver
	json.friend_requests do
		json.array! user.friend_requests_as_receiver do |request|
			json.partial! "users/userSnippet", user: request.requestor
		end
	end
else
	json.friend_requests nil
end

json.blocked_users do
	json.array! user.blocked_users do |blocked_user|
		json.partial! "users/userSnippet", user: blocked_user
	end
end

if user.current_tournaments
	json.current_tournaments do
		json.array! user.current_tournaments do |tour|
			json.partial! "tournaments/tournament", tournament: tour
			json.tournament_status user.tournament_status(tour)
		end
	end
else
	json.current_tournaments nil
end
