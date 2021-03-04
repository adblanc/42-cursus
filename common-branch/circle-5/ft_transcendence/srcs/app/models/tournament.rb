class Tournament < ApplicationRecord
  resourcify
	has_many :tournament_users, dependent: :destroy
	has_many :users, through: :tournament_users
	has_many :games, dependent: :destroy
	has_one_attached :trophy

	enum status: [
		:pending,
		:registration,
		:quarter,
		:semi,
		:final,
		:finished
	]

	validates :name, presence: true
	validates :registration_start, presence: true
	validates :registration_end, presence: true
	validates_with RegistrationDateValidator
	validates :trophy, blob: { content_type: :image, size_range: 1..5.megabytes }

	after_create do
		attach_trophy
		create_tournament_games
		StartRegistrationJob.set(wait_until: registration_start)
			.perform_later(self)
	end

	def self.cron_create
		date = DateTime.now
		begin
			self.create!(
				name: date.strftime("Week %W"),
				registration_start: date,
				registration_end: date + 1.days,
			)
			ActionCable.server.broadcast("tournaments_global", {})
		rescue => e
			puts "Failed to add new cron-tournament: #{e.inspect}"
		end
	end

	def create_tournament_games
	    create_games(:quarter, 4)
	    create_games(:semi, 2)
	    create_games(:final, 1)
	end

	def create_games(round, number)
	    number.times do
	        games.push(Game.create(
	            level: :hard,
	            goal: 9,
	            game_type: :tournament,
	            status: :waiting_tournament,
	            tournament_round: round
	        ))
	    end
	end

	def attach_trophy
		self.trophy.attach(
			io: File.open("default/trophy.jpg", "r"),
			filename: "trophy.jpg",
			"content_type": "image/jpeg",
		) if !self.trophy.attached?
	end

	def owner
		User.all.each do | user |
			if user.has_role?(:owner, self)
				return user
			end
		end
		return nil
	end

	def open_registration?
		registration_start <= DateTime.now && DateTime.now <= registration_end
	end

	def round_one_games
		games.quarter
	end

	def round_two_games
		games.semi
	end

	def round_three_games
		games.final
	end

	def full?
		users.count == 8
	end

	def user_status(user)
		if self.tournament_users.where(user_id: user.id).first
			return self.tournament_users.where(user_id: user.id).first.status
		else
			return nil
		end
	end

	def winner
		if self.finished?
			if self.tournament_users.winner.first.present?
				self.tournament_users.winner.first.user
			else
				return nil
			end
		end
	end

	def push_next_round(winner)
		if self.quarter?
			@status = "semi"
		else
			@status = "final"
		end
		self.games.where(tournament_round: @status).each do | game |
			if game.users.count < 2
				game.users.push(winner)
				game.game_users.where(user: winner).update(status: :pending)
				return
			end
		end
	end

	def set_tournament_user(winner, eliminated)
		if winner
			TournamentUser.where(tournament: self, user: winner).first.update(status: :winner)
			TournamentUser.where(tournament: self, user: eliminated).first.update(status: :eliminated)
		else
			TournamentUser.where(tournament: self, user: eliminated).first.update(status: :eliminated)
		end
	end

	def finish_game(winner, game)
		game.game_users.where(user_id: winner.id).first.update(status: :won)
		game.game_users.where.not(user_id: winner.id).first.update(status: :lose)
		game.update(status: :forfeit)
		game.handle_tournament_end
	end

	def finish_game_without_forfeit(winner, game)
		game.game_users.where(user_id: winner.id).first.update(status: :won)
		game.game_users.where.not(user_id: winner.id).first.update(status: :lose)
		game.update(status: :finished)
		game.handle_tournament_end
	end

	def forfeit_notif(winner, loser, forfeit)
		if forfeit == true
			winner.send_notification("You won your game by forfeit for #{self.name} tournament", "tournaments/#{self.id}", "tournaments")
			loser.send_notification("You lost your game by forfeit for #{self.name} tournament", "tournaments/#{self.id}", "tournaments")
		else
			winner.send_notification("You randomly won your game for #{self.name} tournament", "tournaments/#{self.id}", "tournaments")
			loser.send_notification("You randomly lost your game for #{self.name} tournament", "tournaments/#{self.id}", "tournaments")
		end
	end

	def finish_tournament(winner)
		self.update(status: :finished)
		ActionCable.server.broadcast("tournament_#{self.id}", { eot: true })
		if winner
			User.all.each do |user|
				user.send_notification("#{self.name} tournament is over. Winner is : #{winner.name}", "tournaments/#{self.id}", "tournaments")
			end
		else
			User.all.each do |user|
				user.send_notification("#{self.name} tournament final was not played! Tournament is over and has no winner!", "tournaments/#{self.id}", "tournaments")
			end
		end
	end
end
