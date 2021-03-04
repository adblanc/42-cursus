class RoomsController < ApplicationController
	before_action :authenticate_user!

	def index
		@rooms = @current_user.rooms.empty? ? Room.where(is_private: false) : Room.where('id NOT IN (?) AND is_private = false', @current_user.rooms.ids);
	end

	def show
		@room = Room.find_by_id(params[:id]);

		if (@room)
			@room
		else
			render json: {"room" => ["not found."]}, status: :not_found
		end
	end

	def my_rooms
		if (@current_user.admin?)
			@rooms = Room.where('id IN (?) OR is_dm = false', @current_user.rooms.ids)
		else
			@rooms = @current_user.rooms.select { |room| !@current_user.is_room_ban?(room) }
		end
	end

	def create
		if (room_params[:name].blank?)
			render json: {"name" => ["can't be blank"]}, status: :unprocessable_entity
			return
		/elsif room_params[:is_private] and room_params[:password].blank?
			render json: {"password" => ["can't be blank"]},
				status: :unprocessable_entity
			return/
		elsif !room_params[:is_private] and !room_params[:password].blank?
			render json: {"password" => ["should be blank when creating public channel"]},
				status: :unprocessable_entity
			return
		end

		@room = Room.create(room_params)

		@room.users.push(current_user)
		current_user.add_role :owner, @room
		if room_params[:password] && @room.is_private
			@room.password = BCrypt::Password.create(room_params[:password])
		else
			@room.password = nil
		end

		if @room.save
			@room
		else
			render json: @room.errors, status: :unprocessable_entity
		end
	end

	  def update
		@room = Room.find_by_id(params[:id])
		if !@room
			return render json: {"room" => ["not found."]}, status: :not_found
		end

		if !@current_user.is_room_owner?(@room)
			render json: {"you" => ["must be owner of this room"]}, status: :unprocessable_entity
		elsif !@room.is_private
			render json: {"room" => ["need to be private to have a password"]}, status: :unprocessable_entity
		else
			if params[:password] && !params[:password].empty?
				@room.password = BCrypt::Password.create(params[:password])
			else
				@room.password = nil
			end
			if (@room.save)
				@room
			else
				render json: @room.errors, status: :unprocessable_entity
			end
		end
	  end

	  def join
		if (room_params[:name].blank?)
			render json: {"name" => ["can't be blank"]}, status: :unprocessable_entity	and return;
		end

		@room = Room.find_by(name: room_params[:name])
		if !@room
			return render json: {"name or password" => ["is incorrect."]},	status: :unprocessable_entity
		end

		if (@room.users.exists?(current_user.id))
			return render json: {"You" => ["are already in this room"]}, status: :unprocessable_entity
		end

		if (room_params[:is_private]&.size != 0) && !@room.is_private
			return render json: {"You" => ["can't join public room from here"]}, status: :unprocessable_entity
		end

		if @current_user.is_room_ban?(@room)
			render json: {"you" => ["are banned from this room."]}, status: :unprocessable_entity
		elsif @room.is_dm
			render json: {"you" => ["can't join this room."]}, status: :unprocessable_entity
		else
			if @room.is_private && @room.password && BCrypt::Password.new(@room.password) != room_params[:password]
					return render json: {"name or password" => ["is incorrect."]},
						status: :unprocessable_entity
			end
			@room.users.push(current_user) unless current_user.rooms.exists?(@room.id)
			@room.send_room_notification("join", @current_user, @current_user, nil)
			@room
		end
	end

	def quit
		@room = Room.find_by_id(params[:id])

		if (!@room)
			return;
		elsif (!current_user.rooms.exists?(@room.id))
			render json: {"you" => ["are not in this room."]}, status: :unprocessable_entity
		elsif (@current_user.is_room_ban?(@room));
			render json: {"action" => ["left"]}, status: :ok
		else
			if (@room.remove_user(current_user) === "left")
				@room.send_room_notification("left", @current_user, @current_user, nil)
				render json: {"action" => ["left"]}, status: :ok
			else
				render json: {"action" => ["deleted"]}, status: :ok
			end
		end
	end

	def destroy
		@room = Room.find_by_id(params[:id])

		if (!@room)
			render json: {"room" => ["does not exists"]}, status: :not_found
		elsif (!@current_user.is_room_owner?(@room))
			render json: {"you" => ["must be owner of this room"]}, status: :unprocessable_entity
		else
			@room.destroy
			@room
		end
	end

	def init_direct_messages
		@target_user = User.find_by_id(params[:user_id]);

		if (!@target_user)
			render json: {"user" => ["does not exist"]}, status: :unprocessable_entity
		elsif (@room = Room.where('id IN (?) AND id IN (?) AND is_dm = true', @current_user.rooms.ids, @target_user.rooms.ids).take)
			@room
		else
			@room = Room.create(name: "",
				password: nil, is_dm: true, is_private: true)

			if @room.save
				@room.users.push(@current_user)
				@room.users.push(@target_user)

				@target_user.send_notification("#{@current_user.name} created a conversation with you", "", "dm-creation");
				@room
			else
				render json: @room.errors, status: :unprocessable_entity
			end
		end
	end

	private
	def room_params
		params.permit(:name, :password, :is_private)
	end
end
