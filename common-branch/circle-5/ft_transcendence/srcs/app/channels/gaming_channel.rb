class GamingChannel < ApplicationCable::Channel

  def subscribed
      @id = params[:id]
      @game = Game.find_by_id(@id)


      if !@game or @game.game_ended?
        reject
      end

      stream_from "game_#{@id}"

     self.game_continue
  end

  def player_movement(data)
    if (@game.paused?)
      @game.reload
    end
     if (current_user.is_playing_in?(@game) && @game.started?)
      ActionCable.server.broadcast("game_#{@id}", data);
     end
  end

  def player_score(data)
    if (@game.paused?)
      @game.reload
    end
    if (current_user.is_playing_in?(@game) && @game.started?)
      @game.player_score(data);
     end
  end

  def game_continue
    @game.reload
    if (current_user.is_playing_in?(@game) && @game.paused?)
      current_user.appear("in game")
      @game.check_user_paused(current_user);
    end
  end

  def game_paused
    @game.reload
    if (current_user.is_playing_in?(@game) && (@game.started? || @game.paused?))
      @game.user_paused(current_user);
    end
  end

  def game_started
	GameUser.where({ game_id: @id }).each do |u|
		User.where({ id: u.user_id }).first.appear("in game")
	end
    @game.reload
  end

  def unsubscribed
      self.game_paused
  end
end
