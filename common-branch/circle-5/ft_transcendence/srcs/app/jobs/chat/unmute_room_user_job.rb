class UnmuteRoomUserJob < ApplicationJob
  queue_as :default

  def perform(mute)
    # Do something later
    mute.destroy
  end

end
