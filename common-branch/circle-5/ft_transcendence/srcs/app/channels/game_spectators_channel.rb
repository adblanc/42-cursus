class GameSpectatorsChannel < ApplicationCable::Channel
	def subscribed
		@id = params[:id]
		@channel = "game_spectators_#{@id}";
		@game = Game.find_by_id(@id)


		if !@game or @game.finished?
			reject
		end

		if (current_user.is_spectating?(@game))
			ActionCable.server.broadcast(@channel, data("spectator_joined"));
		end

		stream_from @channel
	end

	def unsubscribed
		if (current_user.is_spectating?(@game))
			ActionCable.server.broadcast(@channel, data("spectator_left"));
			current_user.remove_role(:spectator, @game);
		end
	  # Any cleanup needed when channel is unsubscribed
	end

	private

	def data(action)
		res = {};
		res["action"] = action;
		res["payload"] = {};
		res["payload"] = {"id" => current_user.id, "name" => current_user.name};

		return res;
	end

  end
