class Mute < ApplicationRecord
	belongs_to :room
	belongs_to :muted_user, :class_name => "User"

end
