class Room < ApplicationRecord
	resourcify

	after_destroy :notify_destruction_to_rooms_channel
	before_destroy :unset_games
	after_save		:notify_room_creation

	validates :name, presence: true, uniqueness: true, allow_blank: true, length: {minimum: 0, maximum: 16}
	has_many :room_messages, dependent: :destroy,
						 inverse_of: :room
	has_and_belongs_to_many :users

	has_many :mutes
	has_many :muted_users, :through => :mutes

	has_many :bans
	has_many :banned_users, :through => :bans

	def notify_destruction_to_rooms_channel
		payload = {
			id: self.id,
		}
		ActionCable.server.broadcast("rooms_global", {"action" => "channel_deleted", "payload" => payload});

		mutes.each do |mute|
			remove_mute_job(mute.id)
		end

		bans.each do |ban|
			remove_ban_job(ban.id)
		end
	end

	def remove_mute_job(id)
		queue = Sidekiq::ScheduledSet.new

		jobs = queue.select do |job|
			job.args.first["arguments"].first["_aj_globalid"] == "gid://active-storage/Mute/#{id}"
		end

		jobs.first&.delete
	end

	def remove_ban_job(id)
		queue = Sidekiq::ScheduledSet.new

		jobs = queue.select do |job|
			job.args.first["arguments"].first["_aj_globalid"] == "gid://active-storage/Ban/#{id}"
		end

		jobs.first&.delete
	end

	def unset_games
		self.room_messages.each do |msg|
			if msg.game.present? && msg.game.pending?
				ActionCable.server.broadcast("game_#{msg.game.id}", {"event" => "expired"});
				msg.game.destroy
			end
		end
	end

	def notify_room_creation
		ActionCable.server.broadcast("rooms_global",
			{"action" => if self.is_private or self.is_dm then
				"admin_channel_created" else "channel_created" end, "payload" => nil});
	end

	def valid_update_role_action(action)
		!action.blank? && (action === "promoted" || action === "demoted");
	end

	def update_user_role(user, action)
		case action
		when "promoted"
			if (user.is_member?(self))
				user.add_role :administrator, self
			elsif user.has_role?(:administrator, self)
				owner = User.with_role(:owner, self).first
				owner&.remove_role(:owner, self)
				owner&.add_role(:administrator, self)
				user.add_role(:owner, self)
			end
		when "demoted"
			if (user.is_room_administrator?(self))
				user.remove_role :administrator, self
			end
		end
	end

	def remove_user(user)
		if (self.is_dm)
			self.destroy
			return "destroyed";
		else
			users.delete(user)
			if user.is_room_owner?(self)
				return remove_owner(user)
			elsif user.is_room_administrator?(self)
				user.remove_role(:administrator, self)
			end
		end

		return "left";
	end

	def remove_owner(user)
		user.remove_role(:owner, self)
		if users.blank? || users.size == banned_users.size
			self.destroy
			return "destroyed"
		else
			users.each do |u|
				if !self.bans.exists?(banned_user_id: u.id)
					new_owner = u
					new_owner.remove_role(:administrator, self) if new_owner.is_room_administrator?(self)
					new_owner.add_role(:owner, self)
					return "left";
				end
			end
		end
		return "left";
	end

	def send_room_notification(type, issuer, target, time)
		room_content = room_notification_content(type,issuer, target,time);

		if (room_content)
			room_msg = RoomMessage.create(user: issuer, room: self, content: room_content, is_notification: true);
			ActionCable.server.broadcast("room_#{self.id}", {"message" => room_msg});
		end

		target_content = target_notification_content(type, issuer, time);

		if (target_content)
			target.send_notification(target_content, "", "room");
		end
	end

	def room_notification_content(type, issuer, target, time)
		case type
		when "ban"
			return "#{target.login_with_ang} has been banned #{time} by #{issuer.login_with_ang}"
		when "mute"
			return "#{target.login_with_ang} has been muted #{time} by #{issuer.login_with_ang}"
		when "unban"
			return "#{target.login_with_ang} has been unbanned by #{issuer.login_with_ang}"
		when "unmute"
			return "#{target.login_with_ang} has been unmuted by #{issuer.login_with_ang}"
		when "promoted"
			return "#{target.login_with_ang} has been promoted by #{issuer.login_with_ang}"
		when "demoted"
			return "#{target.login_with_ang} has been demoted by #{issuer.login_with_ang}"
		when "join"
			return "#{target.login_with_ang} has joined"
		when "left"
			return "#{target.login_with_ang} has left"
		else
			return nil;
		end
	end

	def target_notification_content(type, issuer, time)
		case type
		when "ban"
			return "you have been banned #{time} from #{self.name} by #{issuer.login_with_ang}"
		when "mute"
			return nil;
		when "unban"
			return "you have been unbanned from #{self.name} by #{issuer.login_with_ang}"
		when "unmute"
			return "you have been unmuted from #{self.name} by #{issuer.login_with_ang}"
		when "promoted"
			return "you have been promoted in #{self.name} by #{issuer.login_with_ang}"
		when "demoted"
			return "you have been demoted in #{self.name} by #{issuer.login_with_ang}"
		else
			return nil;
		end
	end

	def correct_mute_or_ban_time(time)
		case time
		when "10mn"
			return 10.minutes;
		when "30mn"
			return 30.minutes;
		when "1h"
			return 1.hours;
		when "24h"
			return 24.hours;
		when "indefinitely"
			return "indefinitely";
		else
			return false;
		end
	end

	def expected_mute_or_bantime
		return "Expected: 10mn | 30mn | 1h | 24h | indefinitely";
	end

	def correct_name(current_user)
		name = self.name;

		if (self.is_dm)
			other_user = self.users.where("id != ?", current_user.id).take;

			if (other_user)
				name = other_user.name;
			end

		end

		name ? name : self.name;
	end

end
