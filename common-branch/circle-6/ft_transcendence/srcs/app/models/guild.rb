class Guild < ApplicationRecord
  resourcify
	has_one_attached :img

	has_many :confirmed_users,  -> (object) { where(status: :confirmed) }, class_name: "GuildUser", foreign_key: :guild_id, dependent: :destroy
	has_many :members, through: :confirmed_users, source: :user
	has_many :pending, -> (object) { where(status: :pending) }, class_name: "GuildUser", foreign_key: :guild_id, dependent: :destroy
	has_many :pending_members, through: :pending, source: :user

	has_many :guild_wars
	has_many :wars, through: :guild_wars

	validates :img, blob: { content_type: :image }
	validates :name, presence: true, uniqueness: true, length: {minimum: 5, maximum: 20}
	validates :ang, presence: true, length: {minimum: 2, maximum: 5}

	after_create :attach_img

	def attach_img
		self.img.attach(
			io: File.open("default/guild.jpg", "r"),
			filename: "guild.jpg",
			"content_type": "image/jpeg",
		) if !self.img.attached?
	end

	def remove_user(user)
		members.delete(user)
		user.update(contribution: 0)
		if user.guild_owner?(self)
			remove_owner(user)
			return
		elsif user.guild_officer?(self)
		  user.remove_role(:officer, self)
		end
	end

	def remove_owner(user)
		user.remove_role(:owner, self)
		if members.blank?
			self.destroy
		else
			new_owner = members.first
			new_owner.add_role(:owner, self)
			new_owner.remove_role(:officer, self) if new_owner.guild_officer?(self)
			new_owner.send_notification("The owner of #{self.name} left! You have been automatically appointed owner of #{self.name}.", "/guild/#{self.id}", "guild")
		end
	end

	def is_member?(user)
		user.guild&.id == self.id
	end

	def owner
		User.with_role(:owner, self).first
	end

	def officers
		User.with_role(:officer, self)
	end

	def atWar?
		self.wars.started.present? || self.wars.confirmed.present?
	end

	def pendingWar?
		self.wars.pending.present?
	end

	def warInitiator?
		self.wars.pending.each do |war|
			return true if war.initiator.id == self.id
		end
		return false
	end

	def warOpponent(war)
		war.guilds.where.not(id: self.id).first
	end

	def war_request
		wars.pending.each do |war|
			return war if war.initiator.id == self.id
		end
		return nil
	end

	def activeWar
		wars.where(status: [:started, :confirmed]).first
	end

	def startedWar
		wars.where(status: [:started]).first
	end

	def waitingWar
		wars.pending.where(id: war_request).first
	end

	def pendingWars
		wars.pending.where.not(id: war_request)
	end

	def war_points(war)
		GuildWar.where(guild: self, war: war).first.points
	end

	def war_score(points)
		war = wars.find_by(status: :started)
		if war.present?
			self.guild_wars.find_by(war: war).score(points)
		end
		war.increment!(:nb_games, 1)
	end

	def win_score(points)
		increment!(:points, points)
	end

	def lose_score(points)
		decrement!(:points, points)
	end

end
