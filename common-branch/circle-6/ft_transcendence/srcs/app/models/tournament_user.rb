class TournamentUser < ApplicationRecord
	belongs_to :user
	belongs_to :tournament

	enum status: [
		:competing,
		:eliminated,
		:winner
	]

	validates :user_id, uniqueness: {scope: [:tournament_id]}
end
