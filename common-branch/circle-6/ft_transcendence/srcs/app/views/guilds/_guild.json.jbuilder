json.extract! guild, :id, :name, :ang, :points, :created_at, :updated_at
json.img_url url_for(guild.img) if guild.img.attached?
json.isOwner @current_user.guild_owner?(guild)
json.isInGuild guild.is_member?(@current_user)
json.atWar guild.atWar?
json.pendingWar guild.pendingWar?
json.warInitiator guild.warInitiator?
if guild.activeWar
	json.activeWar do
		json.id guild.activeWar.id
		json.prize guild.activeWar.prize
		json.start guild.activeWar.start
		json.end guild.activeWar.end
		json.status guild.activeWar.status
		json.time_to_answer guild.activeWar.time_to_answer
		json.max_unanswered_calls guild.activeWar.max_unanswered_calls
		json.warPoints guild.activeWar.war_points(guild)
		json.atWarTime guild.activeWar.atWarTime?
		json.partial! "wars/warinclude", war: guild.activeWar
		json.warTimes do
			json.array! guild.activeWar.war_times do |war_time|
				json.partial! "wars/war_time", war_time: war_time
			end
		end
		if guild.activeWar.activeWarTime
			json.activeWarTime do
				json.id guild.activeWar.activeWarTime.id
				json.start guild.activeWar.activeWarTime.start
				json.end guild.activeWar.activeWarTime.end
				json.time_to_answer guild.activeWar.activeWarTime.time_to_answer
				json.max_unanswered_calls guild.activeWar.activeWarTime.max_unanswered_calls
				json.unanswered_calls guild.activeWar.activeWarTime.unanswered_calls
				json.activeGame guild.activeWar.activeWarTime.activeGame
				if guild.activeWar.activeWarTime.pendingGame
					json.pendingGame do
						json.id guild.activeWar.activeWarTime.pendingGame.id
						json.level guild.activeWar.activeWarTime.pendingGame.level
						json.goal guild.activeWar.activeWarTime.pendingGame.goal
						json.users do
							json.array! guild.activeWar.activeWarTime.pendingGame.users do |user|
								json.id user.id
								json.name user.name
							end
						end
					end
					json.pendingGameInitiator guild.activeWar.activeWarTime.pendingGameInitiator
					json.pendingGameGuildInitiator guild.activeWar.activeWarTime.pendingGameGuildInitiator
				else
					json.pendingGame nil
				end
			end
		else
			json.activeWarTime nil
		end
	end
else
	json.activeWar nil
end
if guild.activeWar
	json.warOpponent do
		json.id  guild.warOpponent(guild.activeWar).id
		json.name  guild.warOpponent(guild.activeWar).name
		json.img_url url_for(guild.warOpponent(guild.activeWar).img) if guild.warOpponent(guild.activeWar).img.attached?
		json.warPoints guild.activeWar.war_points(guild.warOpponent(guild.activeWar))
	end
end
if guild.waitingWar
	json.waitingWar do
		json.id guild.waitingWar.id
		json.prize guild.waitingWar.prize
		json.start guild.waitingWar.start
		json.end guild.waitingWar.end
		json.status guild.waitingWar.status
		json.time_to_answer guild.waitingWar.time_to_answer
		json.max_unanswered_calls guild.waitingWar.max_unanswered_calls
		json.partial! "wars/warinclude", war: guild.waitingWar
		json.warTimes do
			json.array! guild.waitingWar.war_times do |war_time|
				json.partial! "wars/war_time", war_time: war_time
			end
		end
	end
else
	json.waitingWar nil
end
if guild.waitingWar
	json.warOpponent do 
		json.id  guild.warOpponent(guild.waitingWar).id
		json.name  guild.warOpponent(guild.waitingWar).name
		json.img_url url_for(guild.warOpponent(guild.waitingWar).img) if guild.warOpponent(guild.waitingWar).img.attached?
	end
end
json.members do
  json.array! guild.members do |member|
	json.partial! "guilds/guildMember", member: member
  end
end
json.pending_members do
  json.array! guild.pending_members do |pending_member|
    json.partial! "guilds/guildMember", member: pending_member
  end
end
json.wars do
		json.array! guild.wars do |war|
		json.id war.id
		json.prize war.prize
		json.status war.status
		json.start war.start
		json.end war.end
		json.nb_games war.nb_games
		json.nb_wartimes war.nb_wartimes
		json.war_points war.war_points(guild)
		json.winner war.winner
		json.warOpponent do
			json.id  guild.warOpponent(war).id
			json.ang  guild.warOpponent(war).ang
			json.war_points  guild.warOpponent(war).war_points(war)
			json.name  guild.warOpponent(war).name
		end
	end
end
json.pendingWars do
		json.array! guild.pendingWars do |pendingWar|
		json.id pendingWar.id
		json.prize pendingWar.prize
		json.status pendingWar.status
		json.start pendingWar.start
		json.end pendingWar.end
		json.time_to_answer pendingWar.time_to_answer
		json.max_unanswered_calls pendingWar.max_unanswered_calls
		json.partial! "wars/warinclude", war: pendingWar
		json.warOpponent do
			json.id  guild.warOpponent(pendingWar).id
			json.name  guild.warOpponent(pendingWar).name
			json.img_url url_for(guild.warOpponent(pendingWar).img) if guild.warOpponent(pendingWar).img.attached?
			json.points  guild.warOpponent(pendingWar).points
		end
		json.warTimes do
			json.array! pendingWar.war_times do |war_time|
				json.partial! "wars/war_time", war_time: war_time
			end
		end
	end
end
