class GuildsController < ApplicationController
	before_action :authenticate_user!

  def index
	@guilds = Guild.all
  end

  def show
	@guild = Guild.find_by_id(params[:id])
	return head :not_found unless @guild
  end

  def new
	guild = Guild.new
  end

  def create
	if current_user.guild.present? || current_user.pending_guild.present?
		render json: {"You" => ["already have a guild or pending guild"]}, status: :unprocessable_entity
		return
    end
	@guild = Guild.create(guild_params)
	if @guild.save
		@guild.members.push(current_user)
		current_user.add_role :owner, @guild
		@guild
	else
		render json: @guild.errors, status: :unprocessable_entity
  	end
  end

  def edit
	@guild = Guild.find_by_id(params[:id])
	if not current_user.guild_owner?(@guild)
		render json: {"You" => ["must be the guild owner"]}, status: :unprocessable_entity
		return
	end
  end

  def update
	@guild = Guild.find_by_id(params[:id])
	if not @guild
		return render json: {"Guild" => ["does not exist"]}, status: :unprocessable_entity
	end
	if not current_user.guild_owner?(@guild)
		render json: {"You" => ["must be the guild owner"]}, status: :unprocessable_entity
		return
	end

	@guild.update(guild_params)
	if @guild.save
		@guild
	else
		render json: @guild.errors, status: :unprocessable_entity
  	end
  end

  def destroy
	@guild = Guild.find_by_id(params[:id])
	if not @guild
		return render json: {"Guild" => ["does not exist"]}, status: :unprocessable_entity
	end
	if not current_user.guild_owner?(@guild)
		render json: {"You" => ["must be the guild owner"]}, status: :unprocessable_entity
		return
	end

	@guild.members.each do |member|
		member.update(contribution: 0)
	end
	@guild.destroy
  end

  def quit
	@guild = Guild.find_by_id(params[:id])
	if not @guild
		return render json: {"Guild" => ["does not exist"]}, status: :unprocessable_entity
	end
	if not current_user.guild == @guild
		render json: {"You" => ["don't belong to this guild"]}, status: :unprocessable_entity
		return
	end

	if @guild.remove_user(current_user)
		@guild
	end
  end

  def promote
	@guild = Guild.find_by(id: params[:id])
	if not @guild
		return render json: {"Guild" => ["does not exist"]}, status: :unprocessable_entity
	end
	if not current_user.guild_owner?(@guild) || current_user.admin?
		render json: {"You" => ["must be the guild owner"]}, status: :unprocessable_entity
		return
	end
    user = User.find_by_id(params[:user_id])
	if user.has_role?(:officer, @guild)
		render json: {"User" => ["is already officer"]}, status: :unprocessable_entity
		return
	end
	if user.add_role(:officer, @guild)
		@guild
	end
	user.send_notification("#{current_user.name} promoted you to Officer for #{@guild.name}", "/guild/#{@guild.id}", "guild")
  end

  def demote
	@guild = Guild.find_by_id(params[:id])
	if not @guild
		return render json: {"Guild" => ["does not exist"]}, status: :unprocessable_entity
	end
	if not current_user.guild_owner?(@guild) || current_user.admin?
		render json: {"You" => ["must be the guild owner"]}, status: :unprocessable_entity
		return
	end

    user = User.find(params[:user_id])
	if not user.has_role?(:officer, @guild)
		render json: {"User" => ["is not an officer"]}, status: :unprocessable_entity
		return
	end
	if user.remove_role(:officer, @guild)
		@guild
	end
	user.send_notification("#{current_user.name} demoted you to Member for #{@guild.name}", "/guild/#{@guild.id}", "guild")
  end

  def fire
	@guild = Guild.find_by_id(params[:id])
	if not @guild
		return render json: {"Guild" => ["does not exist"]}, status: :unprocessable_entity
	end
	if not current_user.guild_owner?(@guild)
		render json: {"You" => ["must be the guild owner"]}, status: :unprocessable_entity
		return
	end

    user = User.find(params[:user_id])
	if (!@guild.members.exists?(user.id))
		return render json: {"User" => ["not found"]}, status: :not_found
	end
	if @guild.remove_user(user)
		@guild
	end
	user.update(contribution: 0)
	user.send_notification("#{current_user.name} fired you from #{@guild.name}", "/guild/#{@guild.id}", "guild")
  end

  def transfer
	@guild = Guild.find_by_id(params[:id])
	if not @guild
		return render json: {"Guild" => ["does not exist"]}, status: :unprocessable_entity
	end
	user = User.find(params[:user_id])
	if not current_user.guild_owner?(@guild) || current_user.admin?
		render json: {"You" => ["must be the guild owner"]}, status: :unprocessable_entity
		return
	end

	if user.guild_owner?(@guild)
		render json: {"This" => ["user is already guild owner"]}, status: :unprocessable_entity
		return
	end

	owner = User.with_role(:owner, @guild).first
	user.add_role(:owner, @guild)
	owner.remove_role(:owner, @guild)
	if owner.add_role(:officer, @guild)
		@guild
	end
	user.send_notification("#{current_user.name} transferred you ownership for #{@guild.name}", "/guild/#{@guild.id}", "guild")
  end

  def join
	@guild = Guild.find_by_id(params[:id])
	if not @guild
		return render json: {"Guild" => ["does not exist"]}, status: :unprocessable_entity
	end
	if current_user.guild.present? || current_user.pending_guild.present?
		render json: {"You" => ["already have a guild or pending guild"]}, status: :unprocessable_entity
		return
    end

	@guild.pending_members.push(current_user)

	(@guild.officers.to_ary << @guild.owner).each do |officers|
		officers.send_notification("#{current_user.name} wants to join #{@guild.name}", "/guild/#{@guild.id}", "guild")
	end
  end

  def accept
	@guild = Guild.find_by_id(params[:id])
	if not @guild
		return render json: {"Guild" => ["does not exist"]}, status: :unprocessable_entity
	end
	if not authorized_for_guild?(current_user, @guild)
		render json: {"You" => ["are not authorized to do this"]}, status: :unprocessable_entity
		return
	end

	pending_member = User.find_by_id(params[:user_id])

	if (!@guild.pending_members.exists?(pending_member.id))
		return render json: {"User" => ["not found"]}, status: :not_found
	end

    @guild.pending_members.delete(pending_member)
	@guild.members.push(pending_member)
	pending_member.send_notification("#{current_user.name} accepted your request to join #{@guild.name}", "/guild/#{@guild.id}", "guild")

	@guild
  end

  def reject
	@guild = Guild.find_by_id(params[:id])
	if not @guild
		return render json: {"Guild" => ["does not exist"]}, status: :unprocessable_entity
	end
	if not authorized_for_guild?(current_user, @guild)
		render json: {"You" => ["are not authorized to do this"]}, status: :unprocessable_entity
		return
	end

    pending_member = User.find_by_id(params[:user_id])

	if (!@guild.pending_members.exists?(pending_member.id))
		return render json: {"User" => ["not found"]}, status: :not_found
	end

    @guild.pending_members.delete(pending_member)
	pending_member.send_notification("#{current_user.name} rejected your request to join #{@guild.name}", "/guild/#{@guild.id}", "guild")

	@guild
  end

  def withdraw
	@guild = Guild.find_by_id(params[:id])
	if not @guild
		return render json: {"Guild" => ["does not exist"]}, status: :unprocessable_entity
	end
	if not current_user.pending_guild == @guild
		render json: {"You" => ["have not requested to join this guild"]}, status: :unprocessable_entity
		return
	end
	@guild.pending_members.delete(current_user)
  end

  private

  def authorized_for_guild?(user, guild)
    user.guild_owner?(guild) || user.guild_officer?(guild)
  end

  def guild_params
	params.permit(:name, :ang, :img)
  end
end
