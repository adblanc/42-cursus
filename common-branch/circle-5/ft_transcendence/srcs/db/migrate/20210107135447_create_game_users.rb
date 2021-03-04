class CreateGameUsers < ActiveRecord::Migration[6.0]
  def change
    create_table :game_users do |t|
      t.belongs_to :game, index: true, foreign_key: true
      t.belongs_to :user, index: true, foreign_key: true
      t.integer :points, default: 0
      t.integer :status, default: 1
      t.integer :pause_nbr, default: 0
      t.datetime :last_pause
      t.integer :pause_duration, default: 30
      t.timestamps
    end
  end
end
