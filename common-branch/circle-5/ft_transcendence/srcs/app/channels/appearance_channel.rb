class AppearanceChannel < ApplicationCable::Channel
  def subscribed
    stream_from "appearance_channel"

    if (current_user.appearing_on == "offline")
      current_user.appear(current_user.inGame? ? "in game" : "online")
    end
  end

  def unsubscribed
    current_user.disappear
  end

  def appear(data)
    current_user.appear(data["appearing_on"])
  end

end
