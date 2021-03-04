class CreateNotifications < ActiveRecord::Migration[6.0]
  def change
    create_table :notifications do |t|
      t.integer :recipient_id
      t.datetime :read_at
	  t.string :message
	  t.string :link
	  t.string :notification_type

      t.timestamps
    end
  end
end
