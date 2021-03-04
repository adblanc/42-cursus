class CreateGuildUser < ActiveRecord::Migration[6.0]
  def change
	create_table :guild_users do |t|	
	  t.timestamps
	  t.integer :status
      t.belongs_to :user, index: true, foreign_key: true
      t.belongs_to :guild, index: true, foreign_key: true
    end
  end
end
