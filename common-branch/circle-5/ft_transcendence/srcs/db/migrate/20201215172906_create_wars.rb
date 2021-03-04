class CreateWars < ActiveRecord::Migration[6.0]
  def change
	create_table :wars do |t|
		t.datetime :start
      	t.datetime :end
		t.integer :prize
		t.integer :status, default: 0
		t.integer :time_to_answer
		t.integer :max_unanswered_calls
		t.integer :nb_games, default: 0
		t.integer :nb_wartimes, default: 0
		t.boolean :inc_ladder, default: 0
		t.boolean :inc_tour, default: 0
		t.boolean :inc_friendly, default: 0
		t.boolean :inc_easy, default: 0
		t.boolean :inc_normal, default: 0
		t.boolean :inc_hard, default: 0
		t.boolean :inc_three, default: 0
		t.boolean :inc_six, default: 0
		t.boolean :inc_nine, default: 0
		t.timestamps
    end
  end
end
