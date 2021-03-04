require 'test_helper'

class RoomsControllerTest < ActionDispatch::IntegrationTest
  test "room show" do
    room = rooms(:one)
    get room_url(room), xhr: true, headers: valid_auth_header()

    assert_response :success
    rsp = @response.parsed_body;

    assert rsp["name"] == "first room"
    assert rsp["is_private"] == false
  end

  test "room show unauthorized if not logged in" do
    room = rooms(:one)
    get room_url(room), xhr: true

    assert_response :unauthorized
  end

  test "room creation with correct name" do

    post rooms_url, xhr: true, headers: valid_auth_header(), params: {name: "123"}

    assert_response :success

    rsp = @response.parsed_body

    assert_not rsp["is_private"], "should not be private"
    assert rsp["isOwner"], "should be owner"
    assert_not rsp["is_dm"], "should not be dm"
    assert rsp["users"][0]["roomRole"] == "Owner", "should be owner"

  end

  test "should not create room with blank name" do

    post rooms_url, xhr: true, headers: valid_auth_header(), params: {name: ""}

    assert_response :unprocessable_entity
  end

  test "should create private room" do

    post rooms_url, xhr: true, headers: valid_auth_header(), params: {name: "private", password: "test", is_private: true}

    assert_response :success

    rsp = @response.parsed_body

    assert rsp["is_private"], "should  e private"
    assert rsp["isOwner"], "should be owner"
    assert_not rsp["is_dm"], "should not be dm"
    assert rsp["users"][0]["roomRole"] == "Owner", "should be owner"
  end

  test "should not create private room if password blank" do

    post rooms_url, xhr: true, headers: valid_auth_header(), params: {name: "private-no", password: "", is_private: true}

    assert_response :unprocessable_entity
  end

  test "should not create public room if password not blank" do

    post rooms_url, xhr: true, headers: valid_auth_header(), params: {name: "private-no", password: "zebi"}

    assert_response :unprocessable_entity
  end

  test "should update room password" do

    post rooms_url, xhr: true, headers: valid_auth_header(), params: {name: "private", password: "test", is_private: true}
    assert_response :success


    put "/api/rooms/#{@response.parsed_body["id"]}", xhr: true, headers: valid_auth_header(), params: {password: "coucou"}
    assert_response :success

    rsp = @response.parsed_body

    assert rsp["is_private"]
    assert rsp["updated_at"] != rsp["created_at"]

  end

  test "should not update room password if is public" do
    post rooms_url, xhr: true, headers: valid_auth_header(), params: {name: "not private room"}
    assert_response :success

    assert_not @response.parsed_body["is_private"]

    put "/api/rooms/#{@response.parsed_body["id"]}", xhr: true, headers: valid_auth_header(), params: {password: "coucou"}
    assert_response :unprocessable_entity
  end


end
