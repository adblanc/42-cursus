class AddEmailToUsers < ActiveRecord::Migration[6.0]
  def change
    add_column :users, :email, :string, :null => "", :default => 'ft.transcendance@gmail.com'
  end
end
