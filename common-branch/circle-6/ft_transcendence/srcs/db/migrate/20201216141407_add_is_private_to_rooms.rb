class AddIsPrivateToRooms < ActiveRecord::Migration[6.0]
  def change
    add_column :rooms, :is_private, :boolean, :default => false
  end
end
