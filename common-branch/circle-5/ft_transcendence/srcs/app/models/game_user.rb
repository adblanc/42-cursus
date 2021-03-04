class GameUser < ApplicationRecord
    belongs_to :game
    belongs_to :user

    enum status: [
		:pending,
		:accepted,
		:won,
		:lose,
		:paused,
		:ready
	]

end
