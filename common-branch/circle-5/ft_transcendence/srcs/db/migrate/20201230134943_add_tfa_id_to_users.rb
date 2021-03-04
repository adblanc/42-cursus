class AddTfaIdToUsers < ActiveRecord::Migration[6.0]
  def change
    add_column :users, :tfa_id, :string, :null => false, :default => ""
  end
end
