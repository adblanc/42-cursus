require 'date'

class User < ApplicationRecord
  rolify
  after_create :assign_default_role
  after_create :assign_ladder_rank

	has_one_attached :avatar
	has_many :notifications, foreign_key: :recipient_id

	has_one :guild_user,  -> (object) { where(status: :confirmed) }, dependent: :destroy
	has_one :guild, through: :guild_user

	has_one :guild_user_pending,  -> (object) { where(status: :pending) }, class_name: "GuildUser", dependent: :destroy
	has_one :pending_guild, through: :guild_user_pending, source: :guild
	has_and_belongs_to_many :rooms

	has_many :game_users
	has_many :games, through: :game_users

	has_many :blocks
	has_many :blocked_users, :through => :blocks

	has_many :friend_requests_as_requestor, foreign_key: :requestor_id, class_name: :FriendRequest
	has_many :friend_requests_as_receiver, foreign_key: :receiver_id, class_name: :FriendRequest
	has_many :friendships
  	has_many :inverse_friendships, :class_name => "Friendship", :foreign_key => "friend_id"

	has_many :tournament_users, dependent: :destroy
	has_many :tournaments, through: :tournament_users

	validates :avatar, blob: { content_type: :image, size_range: 1..5.megabytes }
	validates :name, presence: true
	validates :name, length: {minimum: 3, maximum: 32}, uniqueness: true
	validates :login, presence: true, uniqueness: true
	validates :email, presence: true, format: { with: URI::MailTo::EMAIL_REGEXP }

	after_create :attach_avatar

	def to_spectate_json
		json = {:id => id, :name => name, :avatar_url => Rails.application.routes.url_helpers.rails_blob_path(avatar, only_path: true)}
		json
	end

	def attach_avatar
		self.avatar.attach(
			io: File.open("default/user.jpg", "r"),
			filename: "user.jpg",
			"content_type": "image/jpeg",
		)
	end

	def assign_default_role
		self.add_role(:regular)
	end

	def assign_ladder_rank
		self.update(ladder_rank: self.id)
	end


	def guild_owner?(guild)
		self.has_role?(:owner, guild)
	end

	def guild_officer?(guild)
		self.has_role?(:officer, guild)
	end

	def guild_role?
		case true
		when self.guild_owner?(guild)
			return "Owner"
		when self.guild_officer?(guild)
			return "Officer"
		when self.guild.present?
			return "Member"
		else
			return nil
		end
	end

	def admin?
		self.has_role?(:admin) || self.has_role?(:master)
	end

	def master?
		self.has_role?(:master)
	end

	def room_role(room)
		if self.admin? && self.has_role?(:owner, room)
			return "Owner"
		elsif self.admin?
			return "Global Admin"
		elsif self.is_room_owner?(room)
			return "Owner"
		elsif self.is_room_administrator?(room)
			return "Administrator"
		else
			return "Member"
		end
	end

	def	is_room_owner?(room)
		self.has_role?(:owner, room) || self.admin?
	end

	def is_room_administrator?(room)
		self.has_role?(:administrator, room) || is_room_owner?(room)
	end

	def is_member?(room)
		!is_room_administrator?(room)
	end

	def is_room_mute?(room)
		room.mutes.exists?(muted_user_id: self.id)
	end

	def is_room_ban?(room)
		room.bans.exists?(banned_user_id: self.id)
	end

	def is_blocked?(user)
		if (user == self)
			return false;
		end
		return self.blocks.exists?(blocked_user_id: user.id);
	end

	def	login_with_ang
		ang = self.guild_ang

		return "#{ang ? "[#{ang}] ": ""}#{self.name}";
	end

	def guild_ang
		if (self.guild.present?)
			return self.guild.ang;
		end
		return nil;
	end

	def friends
		friends_array = friendships.map{|friendship| friendship.friend}
		friends_array += inverse_friendships.map{|friendship| friendship.user}
		friends_array.compact
	end

	def is_friend_of?(user)
		friends.each do | friend |
			return true if friend == user
		end
		return false
	end

	def has_requested_friend?(user)
		friend_requests_as_requestor.each do | request |
			return true if request.other(self) == user
		end
		return false
	end

	def has_received_friend?(user)
		friend_requests_as_receiver.each do | request |
			return true if request.other(self) == user
		end
		return false
	end

	def ban_time
		if self.is_banned?
			return Time.at(self.ban).to_datetime.strftime("%d/%m/%Y")
		end
		"-1"
	end

	def is_banned?
		return self.ban != -1
	end

	def guild?
		guild.present?
	end

	def pending_guild?
		if self.pending_guild
			return true
		else
			return nil
		end
	end

	def is_playing_in?(game)
		return self.has_role?(:player, game) || self.has_role?(:host, game);
	end

	def is_spectating?(game)
		return self.has_role?(:spectator, game);
	end

	def appear(appearing_on)
		self.update(is_present: true, appearing_on: appearing_on);

		ActionCable.server.broadcast("appearance_channel", {"event": "appear", "user_id": self.id, "appearing_on": appearing_on});
	end

	def disappear
		self.update(is_present: false, appearing_on: "offline");

		ActionCable.server.broadcast("appearance_channel", {"event": "disappear", "user_id": self.id, "appearing_on": "offline"});
	end

	def game_request
		games.pending.each do |game|
			return game if game.initiator && game.initiator.id == self.id
		end
		return nil
	end

	def pendingGame
		games.pending.where(id: game_request).first
	end

	def matchedGame
		if games.matched.first
			return games.matched.first.id
		else
			return nil
		end
	end

	def currentGame
		if games.started.first
			return games.started.first.id
		elsif games.paused.first
				return games.paused.first.id
		else
			return nil
		end
	end

	def pendingGameToAccept
		games.pending.where.not(id: game_request).where.not(game_type: :tournament).first
	end

	def tournamentToPlay
		if self.games.pending.where(game_type: :tournament).present? || self.games.matched.where(game_type: :tournament).present?
			return true
		else
			return false
		end
	end

	def inGame?
		self.games.started.present? || self.games.paused.present?
	end

	def is_host?(game)
		self.has_role?(:host, game);
	end

	def send_notification(message, link, type)
		@notification = Notification.create(recipient: self, message: message, link: link, notification_type: type)
		ActionCable.server.broadcast("user_#{self.id}", @notification);
	end

	def game_points(game)
		self.game_users.where(game_id: game.id).first&.points
	end

	def game_status(game)
		self.game_users.where(game_id: game.id).first&.status
	end

	def games_finished
		self.games.select do |game|
			game.game_ended?
		end
	end

	def game_won?(game)
		if game.abandon?
			return false
		end
		if game.winner.id == self.id
			return true
		end
		return false
	end

	def current_tournaments
		tournaments.where.not(status: :finished)
	end

	def tournament_status(tournament)
		self.tournament_users.where(tournament_id: tournament.id).first.status
	end

	def won_tournaments
		@arr = []
		tournaments.finished.each do | tour |
			@arr << tour if self.tournament_status(tour) == "winner"
		end
		return @arr
	end

	def winner(game)
		if game.finished? || game.forfeit?
			game.winner == self
		else
			return nil
		end
	end

	#Achievements
	def number_victory
		i = 0
		self.games_finished.each do |game|
			if game.winner == self
				i+= 1
			end
		end
		return i
	end

	def number_loss
		self.games_finished.length - self.number_victory
	end

	def bronze_medal?
		return self.number_victory >= 10
	end

	def silver_medal?
		return self.number_victory >= 25
	end

	def gold_medal?
		return self.number_victory >= 50
	end

	def best_guild?
	 if Guild.order(:points).reverse_order.first == self.guild
		return true
	 end
	 return false
	end

	def high_rank?
		ladder_rank == 1
	end

	def lucky_man?
		i = 0
		self.games_finished.each do |game|
			if game.forfeit? && game.winner == self
				i+= 1
			end
		end
		if i >= 5
			return true
		end
		return false
	end

	def war_won?
		if self.guild
			i = 0
			self.guild.wars.each do |war|
				if war.winner == self.guild.ang
					return true
				end
			end
		end
		return false
	end

	def achievement?
		if (high_rank? || best_guild? || gold_medal? || silver_medal? || bronze_medal? || war_won?)
			return true
		end
		return false
	end
end
