class CreateTournamentUsers < ActiveRecord::Migration[6.0]
  def change
    create_table :tournament_users do |t|
		t.belongs_to :user, index: true, foreign_key: true
		t.belongs_to :tournament, index: true, foreign_key: true
		t.integer :status, default: 0
      t.timestamps
    end
  end
end
