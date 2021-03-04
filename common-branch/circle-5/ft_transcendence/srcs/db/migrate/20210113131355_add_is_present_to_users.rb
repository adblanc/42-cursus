class AddIsPresentToUsers < ActiveRecord::Migration[6.0]
  def change
    add_column :users, :is_present, :boolean, :default => false
  end
end
