class UsersController < ApplicationController
  before_action :authenticate_user!

  def index
      @users = User.all
  end

  def show
    @current_user
  end

  def update
    if @current_user.update(user_params)
        @current_user
    else
      render json: @current_user.errors, status: :unprocessable_entity
    end
  end

  def show_other_user
  	if (@other_user = User.find_by_id(params[:id]))
		@other_user
	else
		render json: { "user" => ["not found"] }, status: :unprocessable_entity
	end
  end

  def ban_other_user
  	if @current_user.admin?
		if (@other_user = User.find_by_id(params[:id]))
			if (@other_user.master?)
				render json: { "User": ["not allowed to do that"] }, status: :unprocessable_entity
			else
				@other_user.update_attributes(:ban => Time.now.to_i)
				render json: {}, status: :ok
			end
		else
			render json: { "User": ["not found"] }, status: :not_found
		end
	else
		render json: { "User": ["not allowed to do that"] }, status: :unprocessable_entity
	end
  end

  def unban_other_user
  	if @current_user.admin?
		if (@other_user = User.find_by_id(params[:id]))
			@other_user.update_attributes(:ban => -1)
			render json: {}, status: :ok
		else
			render json: { "User": ["not found"] }, status: :not_found
		end
	else
		render json: { "User": ["not allowed to do that"] }, status: :unprocessable_entity
	end
  end

  def admin_other_user
  	if @current_user.admin?
		if (@other_user = User.find_by_id(params[:id]))
			@other_user.add_role :admin
			@other_user.send_notification("#{@current_user.name} made you an administrator of the website", "/user/#{@other_user.id}", "administrator")
			render json: {}, status: :ok
		else
			render json: { "User": ["not found"] }, status: :not_found
		end
	else
		render json: { "User": ["not allowed to do that"] }, status: :unprocessable_entity
	end
  end

  def un_admin_other_user
  	if @current_user.admin?
		if (@other_user = User.find_by_id(params[:id]))
			if (@other_user.master?)
				render json: { "User": ["not allowed to do that"] }, status: :unprocessable_entity
			else
				@other_user.remove_role :admin
				@other_user.send_notification("#{@current_user.name} removed your administrator's rights of the website", "/user/#{@other_user.id}", "administrator")
				render json: {}, status: :ok
			end
		else
			render json: { "User": ["not found"] }, status: :not_found
		end
	else
		render json: { "User": ["not allowed to do that"] }, status: :unprocessable_entity
	end
  end

  def update_room_role
		@room = Room.find_by_id(params[:room_id])

		if !@room
			return render json: {"room" => ["not found"]}, status: :not_found
		elsif @room.is_dm
			return render json: {"you" => ["can't update role in dm"]}, status: :unprocessable_entity
		elsif !@current_user.is_room_owner?(@room)
			return render json: {"you" => ["must be owner of this room"]}, status: :unprocessable_entity
		end

		@user_to_update = User.find_by_id(params[:user_id]);

		action = params[:update_action];

		if !@user_to_update
			render json: {"user" => ["not found"]}, status: :not_found and return;
		elsif !(@room.users.exists?(@user_to_update.id))
			render json: {"user" => ["not found in this room"]}, status: :not_found and return;
		elsif !(@room.valid_update_role_action(action))
			render json: {"you" => ["must provide a valid action"]}, status: :unprocessable_entity and return;
		end

		@room.update_user_role(@user_to_update, action)
		@room.send_room_notification(action, @current_user, @user_to_update, nil)

		@user_to_update;
	end

  private

  def user_params
    params.permit(:name, :avatar, :email, :two_fact_auth)
  end
end
