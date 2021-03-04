class MutesController < ApplicationController
	before_action :authenticate_user!
	before_action :load_entities

	def mute
		if (!correct_req("mute"))
			return;
		end
		if (@room.mutes.exists?(muted_user_id: params[:id]))
			render json: {"User" => ["is already muted"]}, status: :unprocessable_entity
		else
			@mute = @room.mutes.build(:muted_user_id => params[:id])
			if (@mute.save)
				@room.send_room_notification("mute", @current_user, @muted_user, @formatted_time)
				if (@time != "indefinitely")
					UnmuteRoomUserJob.set(wait: @time).perform_later(@mute)
				end
				@muted_user
			else
				render json: @mute.errors, status: :unprocessable_entity
			end
		end
	end

	def unmute
		if (!correct_req("unmute"))
			return;
		end
		if !(@mute = @room.mutes.where(muted_user_id: params[:id]).take)
			render json: {"User" => ["is not muted"]}, status: :unprocessable_entity
		else
			@room.send_room_notification("unmute", @current_user, @muted_user, @formatted_time)
			remove_mutes_job()
			UnmuteRoomUserJob.perform_now(@mute)
			@muted_user
		end
	end

	private

	def remove_mutes_job
		queue = Sidekiq::ScheduledSet.new
		queue.each do |job|
			if job.args.first["arguments"].first["_aj_globalid"] == "gid://active-storage/Mute/#{@mute.id}"
				job.delete
			end
		end
	end

	def correct_req(type)
		if (!@muted_user)
			render json: {"user" => ["does not exist"]}, status: :unprocessable_entity
			return false
		elsif (!@room)
			render json: {"room" => ["does not exist"]}, status: :unprocessable_entity
			return false
		elsif @room.is_dm
			render json: {"you" => ["can't mute in dm"]}, status: :unprocessable_entity
			return false
		elsif (!@room.users.exists?(params[:id]))
			render json: {"user" => ["is not in this room"]}, status: :unprocessable_entity
			return false
		elsif (!@time && type == "mute")
			render json: {"mute_time" => ["is not correct. #{@room.expected_mute_or_bantime}"]}, status: :unprocessable_entity
			return false;
		elsif (!@current_user.is_room_administrator?(@room))
			render json: {"you" => ["must be administrator of this room"]}, status: :unprocessable_entity
			return false;
		elsif (@muted_user.is_room_owner?(@room))
			render json: {"you" => ["can't mute the owner of the room or a global admin"]}, status: :unprocessable_entity
			return false;
		end
		return true
	end


	def load_entities
		@room = Room.find_by_id(params[:room_id]);
		@muted_user = User.find_by_id(params[:id]);
		@formatted_time = params[:room_mute_time];
		@time = @room ? @room.correct_mute_or_ban_time(@formatted_time) : false;
	end

  end
