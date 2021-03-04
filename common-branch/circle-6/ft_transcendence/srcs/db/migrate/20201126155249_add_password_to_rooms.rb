class AddPasswordToRooms < ActiveRecord::Migration[6.0]
  def change
    add_column :rooms, :password, :string, :default => nil
  end
end
