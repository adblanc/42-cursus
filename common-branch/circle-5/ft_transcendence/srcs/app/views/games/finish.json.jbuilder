json.partial! "games/game", game: @game
json.users do
  json.array! @game.users do |user|
     json.id user.id
	 json.name user.name
  end
end