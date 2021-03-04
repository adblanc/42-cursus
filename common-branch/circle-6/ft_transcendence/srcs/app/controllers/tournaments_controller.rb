class TournamentsController < ApplicationController
	before_action :authenticate_user!

	def index
		@tournaments = Tournament.all
	end

	def show
		@tournament = Tournament.find_by_id(params[:id])
		return head :not_found unless @tournament
	end

	def create
		if not current_user.admin?
			render json: {"You" => ["are not authorized to do this"]}, status: :unprocessable_entity
			return
		end

		@tournament = Tournament.new(tournament_params)
		if @tournament.save
			current_user.add_role :owner, @tournament
			ActionCable.server.broadcast("tournaments_global", {})
			@tournament
		else
			render json: @tournament.errors, status: :unprocessable_entity
		end
	end

	def register
		@tournament = Tournament.find(params[:id])

		if not @tournament.open_registration?
			render json: {"Tournament" => ["is not open for registration"]}, status: :unprocessable_entity
			return
		elsif @tournament.users.count >= 8
			render json: {"Tournament" => ["is full"]}, status: :unprocessable_entity
			return
		elsif @tournament.tournament_users.where(user_id: current_user.id).first
			render json: {"You" => [" are already registered"]}, status: :unprocessable_entity
			return
		end
		@tournament.users.push(current_user)
		@tournament.games.quarter.each do | game |
			if game.users.count < 2
				game.users.push(current_user)
				game.game_users.where(user: current_user).update(status: :pending)
				ActionCable.server.broadcast("tournament_#{@tournament.id}",
					{ game_id: game.id })
				return
			end
		end
		@tournament
	end

	private
	def tournament_params
		params.permit(:name, :registration_start, :registration_end, :trophy)
	end
end
