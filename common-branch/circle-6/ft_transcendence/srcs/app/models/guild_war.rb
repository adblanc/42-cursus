class GuildWar < ApplicationRecord
	belongs_to :war
	belongs_to :guild 

	enum status: [
		:pending,
		:accepted,
	]

	def score(points)
		increment!(:points, points)
	end
end
