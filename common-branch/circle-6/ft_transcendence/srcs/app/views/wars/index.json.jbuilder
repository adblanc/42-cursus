json.array! @wars do |war|
  json.id war.id
  json.start war.start
  json.end war.end
  json.prize war.prize
  json.status war.status
  json.guilds do
	json.array! war.guilds do |guild|
		json.id guild.id
		json.name guild.name
		json.img_url url_for(guild.img) if guild.img.attached?
		json.war_points war.war_points(guild)
		json.opponent war.opponent(guild)
	end
  end
end