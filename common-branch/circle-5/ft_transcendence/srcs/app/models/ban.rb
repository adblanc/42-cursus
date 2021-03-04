class Ban < ApplicationRecord
	belongs_to :room
	belongs_to :banned_user, :class_name => "User"

end
