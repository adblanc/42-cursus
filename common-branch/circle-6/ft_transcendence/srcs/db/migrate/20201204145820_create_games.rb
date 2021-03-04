class CreateGames < ActiveRecord::Migration[6.0]
  def change
    create_table :games do |t|
      t.string :level
      t.integer :goal
	    t.integer :status, default: 0
	    t.integer :game_type
	    t.integer :tournament_round, default: 0
	    t.belongs_to :war_time, index: true
	    t.belongs_to :room_message
	    t.belongs_to :tournament
      t.timestamps
    end
  end
end
