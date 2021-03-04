json.array! @guilds do |guild|
  json.id guild.id
  json.name guild.name
  json.points guild.points
  json.atWar guild.atWar?
  json.warInitiator guild.warInitiator?
  json.img_url url_for(guild.img) if guild.img.attached?
end