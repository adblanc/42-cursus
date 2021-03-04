class AddOtpSecretKeyToUsers < ActiveRecord::Migration[6.0]
  def change
    add_column :users, :otp_secret_key, :string, :null => false, :default => ""
  end
end
