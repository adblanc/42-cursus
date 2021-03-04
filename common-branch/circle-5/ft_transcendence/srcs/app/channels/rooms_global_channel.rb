class RoomsGlobalChannel < ApplicationCable::Channel
  def subscribed
    stream_from "rooms_global"

  end

  def unsubscribed
    # Any cleanup needed when channel is unsubscribed
  end
end
