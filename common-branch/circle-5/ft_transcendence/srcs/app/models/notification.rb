class Notification < ApplicationRecord
	belongs_to :recipient, class_name: "User"

	scope :unread, ->{ where(read_at: nil) }
end
