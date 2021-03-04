class GuildUser < ApplicationRecord
	belongs_to :user
	belongs_to :guild

	enum status: [
		:pending,
		:confirmed
	]

	validates :user_id, presence: true, uniqueness: true
	validates :guild_id, presence: true
end