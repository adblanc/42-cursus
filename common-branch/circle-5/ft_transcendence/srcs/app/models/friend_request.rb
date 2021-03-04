class FriendRequest < ApplicationRecord
  belongs_to :requestor, class_name: "User"
  belongs_to :receiver, class_name: "User"

  def other(user)
	if user == requestor
		return receiver
	else
		return requestor
	end
  end

end
