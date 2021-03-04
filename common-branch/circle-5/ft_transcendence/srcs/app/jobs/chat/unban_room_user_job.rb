class UnbanRoomUserJob < ApplicationJob
  queue_as :default

  def perform(ban)
    ban.destroy
  end
end
