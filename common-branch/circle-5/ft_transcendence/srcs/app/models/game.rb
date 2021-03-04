class Game < ApplicationRecord
	resourcify

	has_many :game_users, dependent: :destroy
	has_many :users, through: :game_users
	belongs_to :war_time, optional: true
	has_one :room_message
	has_one :tournament

	after_update :broadcast_finished_to_games_spectate_channel if :saved_change_to_status

	enum status: [
		:pending,
		:started,
		:finished,
		:forfeit,
		:waiting_tournament,
		:abandon,
		:paused,
		:matched,
		:chat_expired
	]

	enum game_type: [
		:friendly,
		:chat,
		:ladder,
		:war_time,
		:tournament
	]

	enum tournament_round: [
		:unapplicable,
		:quarter,
		:semi,
		:final
	]

    validates :level,  presence: true
	validates :goal, presence: true

	def broadcast_finished_to_games_spectate_channel
		if 	self.game_ended?
			ActionCable.server.broadcast("games_to_spectate", {"event" => "finished_game", "gameId" => self.id })
		end
	end

	def game_ended?
		return self.finished? || self.forfeit? || self.abandon?
	end

	def to_spectate_json
		json = {:id => id}
		json[:players] = users.map do |u|
			u.to_spectate_json
		end
		json[:spectators] = spectators.as_json(only: [:id, :name])
		json
	end

	### data
	def winner
		if self.finished? || self.forfeit?
			self.game_users.won.first&.user
		end
	end

	def loser
		if self.finished? || self.forfeit?
			self.game_users.lose.first&.user
		end
	end

	def	spectators
		User.with_role(:spectator, self);
	end

	def initiator
		if self.pending? && self.game_users.accepted.first.present?
			self.game_users.accepted.first.user
		end
	end

	def opponent(user)
		if self.users.count == 2
			self.users.where.not(id: user.id).first
		end
	end

	def game_user_opponent(user)
		if self.game_users.count == 2
			self.game_users.where.not(user_id: user.id).first
		end
	end

	### launch
	def add_host(player)
		self.users.push(player)
		player.remove_role(:spectator, self);
		player.add_role(:host, self);
	end

	def add_second_player(player)
		self.add_player_role(player)
		self.users.push(player)
		self.update(status: :matched)
		self.broadcast({"action" => "matched"});
	end

	def add_player_role(player)
		player.remove_role(:spectator, self);
		player.add_role(:player, self);
	end

	def launch_friendly(second_user)
		self.update(status: :matched)
		self.add_second_player(second_user)
		ExpireMatchedGameJob.set(wait: 2.minutes).perform_later(self)
	end

	### run
	def player_score(data)
		game_user = self.game_users.where(user_id: data["playerId"], game_id: self.id).first
		game_user.increment!(:points)

		self.broadcast(data);

		if (game_user.points >= self.goal)
			game_user.update(status: :won)
			looser = self.game_users.where.not(user_id: data["playerId"]).first
			looser.update(status: :lose)
			self.update(status: :finished)
			self.handle_end_cases
			self.broadcast(self.data_over(game_user, looser))
		end
	end

	def user_paused(user)
		player = self.game_users.where(user_id: user.id).first

		player.increment!(:pause_nbr, 1)

		duration = pause_duration_sec(player.pause_nbr)
		pause_time = DateTime.now
		player.update(status: :paused, pause_duration: duration, last_pause: pause_time);
		self.update(status: :paused);
		self.broadcast(self.data_paused(duration, pause_time));

		if (duration == 0)
			PauseGameJob.perform_now(self.id, player.id)
		else
			PauseGameJob.set(wait: duration.seconds).perform_later(self.id, player.id)
		end
	end

	def check_user_paused(user)
		player = self.game_users.where(user_id: user.id).first

		remove_pause_game_jobs(player)

		if (player.paused?)
			player.update(status: :accepted);
		end
		if (self.game_users.paused.size == 0 && self.paused?)
			self.update(status: :started);
			self.broadcast({"action" => "game_continue"});
		end
	end

	def remove_pause_game_jobs(player)
		queue = Sidekiq::ScheduledSet.new
		queue.each do |job|
			if job.args.first["job_class"] == "PauseGameJob" && job.args.first["arguments"].first == self.id && job.args.first["arguments"].last == player.id
				job.delete
			end
		end
	end
	### end

	def give_up(looser)
		looser.update(status: :lose)
		winner = self.game_users.where.not(id: looser.id).first
		winner.update(status: :won)

		self.update(status: :forfeit)
		self.handle_end_cases

		broadcast_end(winner, looser)
	end

	def handle_end_cases
		if self.war_time?
			self.handle_war_time_end
		elsif self.ladder?
			self.handle_ladder_end
		elsif self.tournament?
			self.handle_tournament_end
		else
			self.handle_points
		end
	end

	def handle_war_time_end
		self.handle_points_wt
		self.users.each do |user|
			user.guild.members.each do |member|
				member.send_notification("War time challenge: #{self.winner.name} won against #{self.loser.name}", "/wars", "wars")
			end
		end
	end

	def handle_ladder_end
		self.handle_points
		self.winner.update(ladder_unchallengeable: 0)
		self.loser.update(ladder_unchallengeable: 0)
		if self.winner.ladder_rank > self.loser.ladder_rank
			self.ladder_swap
		else
			self.loser.update(ladder_unchallengeable: self.winner.id)
		end
	end

	def handle_tournament_end
		self.handle_points
		@tournament = Tournament.find_by_id(self.tournament_id)
		if self.final?
			@tournament.set_tournament_user(self.winner, self.loser)
			@tournament.finish_tournament(self.winner)
		else
			@tournament.push_next_round(self.winner)
			@tournament.set_tournament_user(nil, self.loser)
		end
	end

	def ladder_swap
		rank = self.winner.ladder_rank
		self.winner.update(ladder_rank: self.loser.ladder_rank)
		self.loser.update(ladder_rank: rank)
	end

	def broadcast_end(winner, looser)
		self.broadcast(self.data_over(winner, looser))
	end

	def broadcast(data)
		ActionCable.server.broadcast("game_#{self.id}", data);
	end

	### points
	def handle_friendly_game
		@war = self.winner.guild.startedWar
		@level = []
		@goal = []
		@level << (@war.inc_easy ? "easy" : "")
		@level << (@war.inc_normal ? "normal" : "")
		@level << (@war.inc_hard ? "hard" : "")
		@goal << (@war.inc_three ? 3 : 0)
		@goal << (@war.inc_six ? 6 : 0)
		@goal << (@war.inc_nine ? 9 : 0)

		@score = false
		@level.each do | level |
			if level == self.level
				@score = true
			end
		end
		@goal.each do | goal |
			if goal == self.goal && @score
				self.winner.guild.war_score(10)
				@war.update_guilds(self.winner.guild)
			end
		end
	end

	def handle_war_points
		@war = self.winner.guild.startedWar
		if self.ladder? && @war.inc_ladder
			self.winner.guild.war_score(10)
			@war.update_guilds(self.winner.guild)
		elsif self.tournament? && @war.inc_tour
			self.winner.guild.war_score(10)
			@war.update_guilds(self.winner.guild)
		elsif (self.friendly? || self.chat?) && @war.inc_friendly
			self.handle_friendly_game
		end
	end

	def handle_points
		if self.winner.guild?
			if self.final?
				self.winner.guild.increment!(:points, 50)
				self.winner.increment!(:contribution, 50)
			end
			if self.loser.guild?
				if (self.winner.guild != self.loser.guild)
					self.winner.guild.increment!(:points, 10) unless self.final?
					self.winner.increment!(:contribution, 10) unless self.final?
					if self.winner.guild.startedWar && self.loser.guild.startedWar
						if self.winner.guild.startedWar == self.loser.guild.startedWar
							self.handle_war_points
						end
					end
				end
			else
				self.winner.guild.increment!(:points, 10) unless self.final?
				self.winner.increment!(:contribution, 10) unless self.final?
			end
		end
	end

	def handle_points_wt
		self.winner.guild.war_score(10)
		self.winner.guild.increment!(:points, 10)
		self.winner.increment!(:contribution, 10)
		@war = self.winner.guild.startedWar
		@war.update_guilds(self.winner.guild)
	end

	private

	def data_over(winner, looser)
		res = {};
		res["action"] = "game_over";
		res["payload"] = {};
		res["payload"]["winner"] = {
			"id": winner&.user_id,
			"points": winner&.points,
			"status": :won
		};
		res["payload"]["looser"] = {
			"id": looser&.user_id,
			"points": looser&.points,
			"status": :lose
		};

		if (winner)
			User.where({ id: winner.user_id }).first.appear("online")
		end
		if (looser)
			User.where({ id: looser.user_id }).first.appear("online")
		end
		return res;
	end

	def data_paused(duration, pause_time)
		res = {};
		res["action"] = "game_paused";
		res["payload"] = {};
		res["payload"]["pause_duration"] = duration;
		res["payload"]["last_pause"] = pause_time;

		return res;
	end

	def pause_duration_sec(pause_nbr)
		case pause_nbr
		when 1
			30
		when 2
			15
		when 3
			10
		else
			0
		end
	end

end
