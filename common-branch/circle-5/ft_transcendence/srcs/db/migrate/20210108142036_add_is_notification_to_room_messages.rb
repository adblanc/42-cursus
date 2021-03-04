class AddIsNotificationToRoomMessages < ActiveRecord::Migration[6.0]
  def change
    add_column :room_messages, :is_notification, :boolean, :default => false
  end
end
