class War < ApplicationRecord
	has_many :guild_wars, dependent: :destroy
	has_many :guilds, through: :guild_wars, source: :guild, foreign_key: :guild_id
	accepts_nested_attributes_for :guilds

	has_many :war_times, dependent: :destroy, :validate => false

	enum status: [
		:pending,
		:confirmed,
		:started,
		:ended,
	]

	validates :start, presence: true
	validates :end, presence: true
	validates :prize, presence: true, numericality: { only_integer: true, greater_than_or_equal_to: 2 }
	validates :time_to_answer, presence: true, numericality: { only_integer: true, greater_than_or_equal_to: 1 }
	validates :max_unanswered_calls, allow_blank: true, numericality: { only_integer: true, greater_than_or_equal_to: 1 }
	validates_with WarDateValidator
	validates_with WarIncludesValidator

	def opponent(guild)
		self.guilds.where.not(id: guild.id).first
	end

	def initiator
		if self.pending?
			self.guild_wars.accepted.first.guild
		end
	end

	def atWarTime?
		self.war_times.active.present?
	end

	def activeWarTime
		WarTime.where(war: self, status: :active).first
	end

	def war_points(guild)
		GuildWar.where(war: self, guild: guild).first.points
	end

	def winner
		@points = 0
		if self.ended?
			self.guilds.each do | guild |
				if @points < guild.war_points(self)
					@winner = guild.ang
					@points = guild.war_points(self)
				elsif @points == guild.war_points(self)
					@winner = "tie"
				end
			end
			return @winner
		else
			return nil 
		end
	end

	def update_guilds(winner)
		self.guilds.each do |guild|
			guild.members.each do |member|
				member.send_notification("#{winner.name} earned war points!", "/wars", "wars")
			end
		end
	end
end
