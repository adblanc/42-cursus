class NotificationsChannel < ApplicationCable::Channel
	def subscribed
		user_id = params[:user_id];

		if (user_id != current_user.id)
			reject
		end

    	stream_from "user_#{user_id}"

	  notifications = Notification.where(recipient_id: user_id).order(created_at: :asc).each do |notification|
		transmit(notification.as_json(nil).merge(:ancient => true))
	  end
	end

	def unsubscribed
	  # Any cleanup needed when channel is unsubscribed
	end
  end
