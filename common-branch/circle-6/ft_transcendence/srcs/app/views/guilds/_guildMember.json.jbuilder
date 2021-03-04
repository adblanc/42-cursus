json.extract! member, :id, :name, :contribution, :is_present, :appearing_on
json.inGame member.appearing_on == "in game"
json.avatar_url url_for(member.avatar) if member.avatar.attached?
json.guild_role member.guild_role?
json.admin member.admin?
json.is_friend @current_user.is_friend_of?(member);

