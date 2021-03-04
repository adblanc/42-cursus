class AddIsDmToRooms < ActiveRecord::Migration[6.0]
  def change
    add_column :rooms, :is_dm, :boolean, :default => false
  end
end
