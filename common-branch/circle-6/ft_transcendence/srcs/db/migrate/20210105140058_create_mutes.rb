class CreateMutes < ActiveRecord::Migration[6.0]
  def change
    create_table :mutes do |t|
      t.integer :room_id
      t.integer :muted_user_id

      t.timestamps
    end
  end
end
