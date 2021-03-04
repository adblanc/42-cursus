class AddTfaErrorNbToUsers < ActiveRecord::Migration[6.0]
  def change
    add_column :users, :tfa_error_nb, :integer, :null => false, :default => 0
  end
end
