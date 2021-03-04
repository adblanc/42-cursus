class CreateGuilds < ActiveRecord::Migration[6.0]
  def change
    create_table :guilds do |t|
      t.string :name
	  t.string :ang
	  t.integer :points, default: 0
      t.timestamps
    end
  end
end
