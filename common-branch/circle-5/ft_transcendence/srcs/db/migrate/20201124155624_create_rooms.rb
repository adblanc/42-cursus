class CreateRooms < ActiveRecord::Migration[6.0]
  def change
    create_table :rooms do |t|
      t.string :name, :default => "", :null => ""
      t.timestamps
    end
  end
end
