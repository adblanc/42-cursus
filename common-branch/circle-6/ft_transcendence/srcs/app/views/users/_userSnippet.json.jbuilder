json.extract! user, :id, :name, :is_present, :appearing_on
json.inGame user.appearing_on == "in game"
json.avatar_url url_for(user.avatar) if user.avatar.attached?
json.ladder_rank user.ladder_rank
