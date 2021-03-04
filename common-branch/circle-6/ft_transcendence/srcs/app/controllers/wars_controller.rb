class WarsController < ApplicationController
	before_action :authenticate_user!

	def index
		@wars = War.where(status: :started)
	end

	def show
		@war = War.find_by_id(params[:id])
		return head :not_found unless @war
	end

	def create
		@initiator = Guild.find(params[:initiator_id])
		@recipient = Guild.find(params[:recipient_id])
		@warTimes = JSON.parse(params[:wt_dates])

		if not current_user.guild_owner?(@initiator)
			render json: {"You" => ["must be a guild owner"]}, status: :unprocessable_entity
			return
		end

		if params[:prize].to_i > @initiator.points || params[:prize].to_i > @recipient.points
			render json: {"One" => ["or both guilds cannot wager that many points"]}, status: :unprocessable_entity
			return
		end

		if @warTimes.size == 0
			render json: {"There" => ["must be at least one War Time scheduled"]}, status: :unprocessable_entity
			return
		end

		if @initiator.atWar? || @initiator.warInitiator? || @recipient.atWar?
			render json: {"Your" => ["guild or opponent guild is already at war"]}, status: :unprocessable_entity
			return
		end
		@war = War.create(war_params)
		if @war.save
			@warTimes.each do | wartime |
				@wartime = WarTime.create(war: @war, start: wartime["start"].to_datetime, end: wartime["end"].to_datetime, time_to_answer: @war.time_to_answer, max_unanswered_calls: @war.max_unanswered_calls)
				if not @wartime.save
					render json: @wartime.errors, status: :unprocessable_entity
					@war.destroy
					return
				end
			end
			self.after_creation(@war, @initiator, @recipient)
			@war
		else
			render json: @war.errors, status: :unprocessable_entity
		end
	end

	def accept
		@war = War.find_by_id(params[:id])
		@guild = Guild.find_by_id(current_user.guild.id)
		@opponent = @war.opponent(@guild)
		@guild_war = GuildWar.where(war: @war, guild: @guild).first

		if not current_user.guild_owner?(@guild) || current_user.guild_officer?(@guild)
			render json: {"You" => ["must be a guild owner or officer to do this"]}, status: :unprocessable_entity
			return
		end

		if @guild.atWar? || @guild.warInitiator? || @opponent.atWar?
			render json: {"Your" => ["guild or opponent guild is already at war"]}, status: :unprocessable_entity
			return
		end

		@guild_war.update(status: :accepted)
		@war.update(status: :confirmed)

		@guild.wars.where(status: :pending).each do |war|
			war.opponent(@guild).members.each do |member|
				member.send_notification("#{@guild.name} rejected your guild's war declaration", "/wars", "wars")
			end
			queue = Sidekiq::ScheduledSet.new
			queue.each do |job|
				if job.args.first["arguments"].first["_aj_globalid"] == "gid://active-storage/War/#{war.id}"
					job.delete
				end
			end
			war.destroy
		end

		if @war.save
			@war
		end

		@opponent.members.each do |member|
			member.send_notification("#{@guild.name} has accepted your guild's war declaration", "/wars", "wars")
		end

		StartWarJob.set(wait_until: @war.start).perform_later(@war)
		EndWarJob.set(wait_until: @war.end).perform_later(@war)
		@war.war_times.each do | wt |
			StartWarTimeJob.set(wait_until: wt.start).perform_later(wt, @war)
		end
	end

	def reject
		@war = War.find_by_id(params[:id])
		@guild = Guild.find_by_id(current_user.guild.id)

		if not current_user.guild_owner?(@guild) || current_user.guild_officer?(@guild)
			render json: {"You" => ["must be a guild owner or officer to do this"]}, status: :unprocessable_entity
			return
		end
		if @guild.atWar? || @guild.warInitiator?
			render json: {"Your" => ["Guild is at war or has already declared war"]}, status: :unprocessable_entity
			return
		end

		@war.opponent(@guild).members.each do |member|
			member.send_notification("#{@guild.name} rejected your guild's war declaration", "/wars", "wars")
		end
		queue = Sidekiq::ScheduledSet.new
		queue.each do |job|
			if job.args.first["arguments"].first["_aj_globalid"] == "gid://active-storage/War/#{@war.id}"
				job.delete
			end
		end
		@war.destroy
	end

	def update
		@war = War.find_by_id(params[:id])
		@guild = Guild.find_by_id(current_user.guild.id)
		@opponent = @war.opponent(@guild)
		@gw_initiator = GuildWar.where(war: @war, guild: @guild).first
		@gw_recipient = GuildWar.where(war: @war).where.not(guild: @guild).first

		if params[:prize].to_i > @guild.points || params[:prize].to_i > @opponent.points
			render json: {"One" => ["or both guilds cannot wager that many points"]}, status: :unprocessable_entity
			return
		end

		if not current_user.guild_owner?(@guild) || current_user.guild_officer?(@guild)
			render json: {"You" => ["must be a guild owner or officer to do this"]}, status: :unprocessable_entity
			return
		end
		if @guild.atWar? || @guild.warInitiator? || @opponent.atWar?
			render json: {"Your" => ["guild or opponent guild is already at war"]}, status: :unprocessable_entity
			return
		end
		@wt_change = params[:wt_change]
		if @wt_change
			@warTimes = JSON.parse(params[:wt_dates])
			if @warTimes.size == 0
				render json: {"There" => ["must be at least one War Time scheduled"]}, status: :unprocessable_entity
				return
			end
			@war.war_times.each do | wt |
				wt.delete
			end
			@warTimes.each do | wartime |
				@wartime = WarTime.create(war: @war, start: wartime["start"].to_datetime, end: wartime["end"].to_datetime, time_to_answer: @war.time_to_answer, max_unanswered_calls: @war.max_unanswered_calls)
				if not @wartime.save
					render json: @wartime.errors, status: :unprocessable_entity
					return
				end
			end
		end

		@war.update(war_params)
		if @war.save
			@gw_initiator.update(status: :accepted)
			@gw_recipient.update(status: :pending)
			@guild.wars.where(status: :pending).each do |war|
				if war != @war
					war.opponent(@guild).members.each do |member|
						member.send_notification("#{@guild.name} rejected your guild's war declaration", "/wars", "wars")
					end
					queue = Sidekiq::ScheduledSet.new
					queue.each do |job|
						if job.args.first["arguments"].first["_aj_globalid"] == "gid://active-storage/War/#{war.id}"
							job.delete
						end
					end
					war.destroy
				end
			end
			@opponent.members.each do |member|
				member.send_notification("#{@guild.name} has negotiated the terms of your guild's war declaration", "/wars", "wars")
			end

			queue = Sidekiq::ScheduledSet.new
			queue.each do |job|
				if job.args.first["arguments"].first["_aj_globalid"] == "gid://active-storage/War/#{@war.id}"
					job.delete
				end
			end
			ExpireWarJob.set(wait_until: @war.end).perform_later(@war)
			@war
		else
			render json: @war.errors, status: :unprocessable_entity
		end
	end

	private

	def war_params
		params.permit( :start, :end, :prize, :time_to_answer, :max_unanswered_calls, :inc_ladder, :inc_tour, :inc_friendly,
		:inc_easy, :inc_normal, :inc_hard, :inc_three, :inc_six, :inc_nine)
	end

	def after_creation(war, initiator, recipient)
		GuildWar.create!(guild: initiator, war: war, status: :accepted)
		GuildWar.create!(guild: recipient, war: war, status: :pending)
		initiator.wars.where(status: :pending).each do |other_war|
			if other_war != war
				other_war.opponent(initiator).members.each do |member|
					member.send_notification("#{initiator.name} rejected your guild's war declaration", "/wars", "wars")
				end
				queue = Sidekiq::ScheduledSet.new
				queue.each do |job|
					if job.args.first["arguments"].first["_aj_globalid"] == "gid://active-storage/War/#{other_war.id}"
						job.delete
					end
				end
				other_war.destroy
			end
		end
		recipient.members.each do |member|
			member.send_notification("#{initiator.name} has declared war to your Guild", "/wars", "wars")
		end
		initiator.members.each do |member|
			member.send_notification("Your guild has declared war to #{recipient.name}", "/wars", "wars")
		end
		ExpireWarJob.set(wait_until: @war.end).perform_later(war)
	end

end
