class BansController < ApplicationController
	before_action :authenticate_user!
	before_action :load_entities

	def ban
		if (!correct_req("ban"))
			return ;
		end
		if (@room.bans.exists?(banned_user_id: params[:id]))
			render json: {"User" => ["is already banned"]}, status: :unprocessable_entity
		else
			@ban = @room.bans.build(:banned_user_id => params[:id])
			if (@ban.save)
				@room.send_room_notification("ban", @current_user, @banned_user, @formatted_time)
				if (@time != "indefinitely")
					UnbanRoomUserJob.set(wait: @time).perform_later(@ban)
				end
				@banned_user
			else
				render json: @ban.errors, status: :unprocessable_entity
			end
		end
	end

	def unban
		if (!correct_req("unban"))
			return ;
		end
		if !(@ban = @room.bans.where(banned_user_id: params[:id]).take)
			render json: {"User" => ["is not banned"]}, status: :unprocessable_entity
		else
			@room.send_room_notification("unban", @current_user, @banned_user, @formatted_time)
			remove_bans_job()
			UnbanRoomUserJob.perform_now(@ban)
			@banned_user
		end
	end

	private

	def remove_bans_job
		queue = Sidekiq::ScheduledSet.new
		queue.each do |job|
			if job.args.first["arguments"].first["_aj_globalid"] == "gid://active-storage/Ban/#{@ban.id}"
				job.delete
			end
		end
	end

	def correct_req(type)
		if (!@banned_user)
			render json: {"user" => ["does not exist"]}, status: :unprocessable_entity
			return false
		elsif (!@room)
			render json: {"room" => ["does not exist"]}, status: :unprocessable_entity
			return false
		elsif @room.is_dm
			render json: {"you" => ["can't ban in dm"]}, status: :unprocessable_entity
			return false
		elsif (!@room.users.exists?(params[:id]))
			render json: {"user" => ["is not in this room"]}, status: :unprocessable_entity
			return false
		elsif (!@time && type == "ban")
			render json: {"ban_time" => ["is not correct. #{@room.expected_mute_or_bantime}"]}, status: :unprocessable_entity
			return false;
		elsif (!@current_user.is_room_administrator?(@room))
			render json: {"you" => ["must be administrator of this room"]}, status: :unprocessable_entity
			return false;
		elsif (@banned_user.is_room_owner?(@room))
			render json: {"you" => ["can't ban the owner of the room or a global admin"]}, status: :unprocessable_entity
			return false;
		end
		return true
	end


	def load_entities
		@room = Room.find_by_id(params[:room_id]);
		@banned_user = User.find_by_id(params[:id]);
		@formatted_time = params[:room_ban_time];
		@time = @room ? @room.correct_mute_or_ban_time(@formatted_time) : false;
	end

  end
