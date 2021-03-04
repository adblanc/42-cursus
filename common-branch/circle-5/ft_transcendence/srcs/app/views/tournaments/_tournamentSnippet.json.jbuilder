json.extract! tournament, :id, :name
json.trophy_url url_for(tournament.trophy) if tournament.trophy.attached?
