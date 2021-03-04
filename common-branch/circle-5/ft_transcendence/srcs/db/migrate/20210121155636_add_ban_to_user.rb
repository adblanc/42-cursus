class AddBanToUser < ActiveRecord::Migration[6.0]
  def change
    add_column :users, :ban, :integer, :null => -1, :default => -1
  end
end
