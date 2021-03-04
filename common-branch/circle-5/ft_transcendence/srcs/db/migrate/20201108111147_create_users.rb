class CreateUsers < ActiveRecord::Migration[6.0]
  def change
  create_table :users do |t|
	  t.belongs_to :guild
      t.string :login
	  t.string :name
	  t.integer :contribution, default: 0
	  t.integer :ladder_rank
	  t.integer :ladder_unchallengeable, default: 0
      t.timestamps
    end
    add_index :users, :name, unique: true
  end
end
