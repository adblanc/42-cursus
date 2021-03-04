class RoomMessage < ApplicationRecord
  belongs_to :user
  belongs_to :room, inverse_of: :room_messages
  has_one :game

  def as_json(options)
    super(options).merge(avatar_url: Rails.application.routes.url_helpers.rails_blob_path(user.avatar, only_path: true), pseudo: user.login_with_ang)
  end
end
