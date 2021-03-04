json.partial! "users/user", user: @current_user
json.notifications do
  json.array! @current_user.notifications do |notification|
     json.id notification.id
	 json.message notification.message
	 json.link notification.link
	 json.created_at notification.created_at
  end
end
