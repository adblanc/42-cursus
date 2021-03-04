class AddTwoFactAuthToUsers < ActiveRecord::Migration[6.0]
  def change
    add_column :users, :two_fact_auth, :boolean, :null => false, :default => false
  end
end
