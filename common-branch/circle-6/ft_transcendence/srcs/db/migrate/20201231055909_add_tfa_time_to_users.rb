class AddTfaTimeToUsers < ActiveRecord::Migration[6.0]
  def change
    add_column :users, :tfa_time, :integer, :null => false, :default => 0
  end
end
