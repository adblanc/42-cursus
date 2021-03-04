require 'test_helper'

class UserTest < ActiveSupport::TestCase
  test "the truth" do
    assert true
  end


  test "should not save user without login" do
    user = User.new(name: "test", email: "test@test.com")
    assert_not user.save, "Saved the user without login"
  end


  test "should have unique login" do
    user = User.new(name: "uniq", login: "uniq", email: "test@test.com")
    assert user.save

    new_user = User.new(name: "eweww", login: "uniq", email: "ewew@ewew.com")

    assert_not new_user.save, "Saved the user with same login"
  end

  test "should have default avatar" do
    user = User.new(name: "test", login: "test", email: "test@test.com")
    assert user.save

    assert user.avatar.attached?, "User have no avatar attached after creation"
    assert user.avatar.filename.to_s == "user.jpg", "User default avatar is not user.jpg"
  end

end
