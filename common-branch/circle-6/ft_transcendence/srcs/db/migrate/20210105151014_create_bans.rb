class CreateBans < ActiveRecord::Migration[6.0]
  def change
    create_table :bans do |t|
      t.integer :room_id
      t.integer :banned_user_id

      t.timestamps
    end
  end
end
