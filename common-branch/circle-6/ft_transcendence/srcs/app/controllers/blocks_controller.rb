class BlocksController < ApplicationController
	before_action :authenticate_user!

	def block
		if (@current_user.blocks.where(blocked_user_id: params[:id]).take)
			render json: {"User" => ["is already blocked"]}, status: :unprocessable_entity
		else
			@blocked = @current_user.blocks.build(:blocked_user_id => params[:id])
			if @blocked.save
				@current_user
			else
				render json: @blocked.errors, status: :unprocessable_entity
			end
		end
	end

	def unblock
		@blocked = @current_user.blocks.where(blocked_user_id: params[:id]).take;
		if (@blocked)
			if (@blocked.destroy)
				@current_user
			else
				render json: @blocked.errors, status: :unprocessable_entity
			end
		else
			render json: {"User" => ["is already unblocked"]}, status: :unprocessable_entity
		end
	end

  end
