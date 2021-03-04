class AddAppearingOnToUsers < ActiveRecord::Migration[6.0]
  def change
    add_column :users, :appearing_on, :string, :default => "offline"
  end
end
