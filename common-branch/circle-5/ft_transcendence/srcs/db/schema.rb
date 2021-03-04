# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# This file is the source Rails uses to define your schema when running `rails
# db:schema:load`. When creating a new database, `rails db:schema:load` tends to
# be faster and is potentially less error prone than running all of your
# migrations from scratch. Old migrations may fail to apply correctly if those
# migrations use external dependencies or application code.
#
# It's strongly recommended that you check this file into your version control system.

ActiveRecord::Schema.define(version: 2021_02_01_175713) do

  # These are extensions that must be enabled in order to support this database
  enable_extension "plpgsql"

  create_table "active_storage_attachments", force: :cascade do |t|
    t.string "name", null: false
    t.string "record_type", null: false
    t.bigint "record_id", null: false
    t.bigint "blob_id", null: false
    t.datetime "created_at", null: false
    t.index ["blob_id"], name: "index_active_storage_attachments_on_blob_id"
    t.index ["record_type", "record_id", "name", "blob_id"], name: "index_active_storage_attachments_uniqueness", unique: true
  end

  create_table "active_storage_blobs", force: :cascade do |t|
    t.string "key", null: false
    t.string "filename", null: false
    t.string "content_type"
    t.text "metadata"
    t.bigint "byte_size", null: false
    t.string "checksum", null: false
    t.datetime "created_at", null: false
    t.index ["key"], name: "index_active_storage_blobs_on_key", unique: true
  end

  create_table "bans", force: :cascade do |t|
    t.integer "room_id"
    t.integer "banned_user_id"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
  end

  create_table "blocks", force: :cascade do |t|
    t.integer "user_id"
    t.integer "blocked_user_id"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
  end

  create_table "friend_requests", force: :cascade do |t|
    t.integer "requestor_id"
    t.integer "receiver_id"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
  end

  create_table "friendships", force: :cascade do |t|
    t.bigint "user_id"
    t.bigint "friend_id"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["friend_id"], name: "index_friendships_on_friend_id"
    t.index ["user_id"], name: "index_friendships_on_user_id"
  end

  create_table "game_users", force: :cascade do |t|
    t.bigint "game_id"
    t.bigint "user_id"
    t.integer "points", default: 0
    t.integer "status", default: 1
    t.integer "pause_nbr", default: 0
    t.datetime "last_pause"
    t.integer "pause_duration", default: 30
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["game_id"], name: "index_game_users_on_game_id"
    t.index ["user_id"], name: "index_game_users_on_user_id"
  end

  create_table "games", force: :cascade do |t|
    t.string "level"
    t.integer "goal"
    t.integer "status", default: 0
    t.integer "game_type"
    t.integer "tournament_round", default: 0
    t.bigint "war_time_id"
    t.bigint "room_message_id"
    t.bigint "tournament_id"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["room_message_id"], name: "index_games_on_room_message_id"
    t.index ["tournament_id"], name: "index_games_on_tournament_id"
    t.index ["war_time_id"], name: "index_games_on_war_time_id"
  end

  create_table "games_users", id: false, force: :cascade do |t|
    t.bigint "user_id", null: false
    t.bigint "game_id", null: false
  end

  create_table "guild_users", force: :cascade do |t|
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.integer "status"
    t.bigint "user_id"
    t.bigint "guild_id"
    t.index ["guild_id"], name: "index_guild_users_on_guild_id"
    t.index ["user_id"], name: "index_guild_users_on_user_id"
  end

  create_table "guild_wars", force: :cascade do |t|
    t.bigint "war_id"
    t.bigint "guild_id"
    t.integer "points", default: 0
    t.integer "status", default: 0
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["guild_id"], name: "index_guild_wars_on_guild_id"
    t.index ["war_id"], name: "index_guild_wars_on_war_id"
  end

  create_table "guilds", force: :cascade do |t|
    t.string "name"
    t.string "ang"
    t.integer "points", default: 0
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
  end

  create_table "mutes", force: :cascade do |t|
    t.integer "room_id"
    t.integer "muted_user_id"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
  end

  create_table "notifications", force: :cascade do |t|
    t.integer "recipient_id"
    t.datetime "read_at"
    t.string "message"
    t.string "link"
    t.string "notification_type"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
  end

  create_table "roles", force: :cascade do |t|
    t.string "name"
    t.string "resource_type"
    t.bigint "resource_id"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["name", "resource_type", "resource_id"], name: "index_roles_on_name_and_resource_type_and_resource_id"
    t.index ["resource_type", "resource_id"], name: "index_roles_on_resource_type_and_resource_id"
  end

  create_table "room_messages", force: :cascade do |t|
    t.bigint "room_id", null: false
    t.bigint "user_id", null: false
    t.bigint "game_id"
    t.text "content"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.boolean "is_notification", default: false
    t.index ["game_id"], name: "index_room_messages_on_game_id"
    t.index ["room_id"], name: "index_room_messages_on_room_id"
    t.index ["user_id"], name: "index_room_messages_on_user_id"
  end

  create_table "rooms", force: :cascade do |t|
    t.string "name", default: ""
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.string "password"
    t.boolean "is_private", default: false
    t.boolean "is_dm", default: false
  end

  create_table "rooms_users", id: false, force: :cascade do |t|
    t.bigint "user_id", null: false
    t.bigint "room_id", null: false
  end

  create_table "tournament_users", force: :cascade do |t|
    t.bigint "user_id"
    t.bigint "tournament_id"
    t.integer "status", default: 0
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["tournament_id"], name: "index_tournament_users_on_tournament_id"
    t.index ["user_id"], name: "index_tournament_users_on_user_id"
  end

  create_table "tournaments", force: :cascade do |t|
    t.string "name"
    t.integer "status", default: 0
    t.datetime "registration_start"
    t.datetime "registration_end"
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
  end

  create_table "users", force: :cascade do |t|
    t.bigint "guild_id"
    t.string "login"
    t.string "name"
    t.integer "contribution", default: 0
    t.integer "ladder_rank"
    t.integer "ladder_unchallengeable", default: 0
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.string "email", default: "ft.transcendance@gmail.com"
    t.boolean "two_fact_auth", default: false, null: false
    t.string "otp_secret_key", default: "", null: false
    t.integer "otp_count", default: 0, null: false
    t.string "tfa_id", default: "", null: false
    t.integer "tfa_error_nb", default: 0, null: false
    t.integer "tfa_time", default: 0, null: false
    t.boolean "is_present", default: false
    t.string "appearing_on", default: "offline"
    t.integer "ban", default: -1
    t.index ["guild_id"], name: "index_users_on_guild_id"
    t.index ["name"], name: "index_users_on_name", unique: true
  end

  create_table "users_roles", id: false, force: :cascade do |t|
    t.bigint "user_id"
    t.bigint "role_id"
    t.index ["role_id"], name: "index_users_roles_on_role_id"
    t.index ["user_id", "role_id"], name: "index_users_roles_on_user_id_and_role_id"
    t.index ["user_id"], name: "index_users_roles_on_user_id"
  end

  create_table "war_times", force: :cascade do |t|
    t.bigint "war_id"
    t.datetime "start"
    t.datetime "end"
    t.integer "status", default: 0
    t.integer "time_to_answer"
    t.integer "max_unanswered_calls", default: 0
    t.integer "unanswered_calls", default: 0
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
    t.index ["war_id"], name: "index_war_times_on_war_id"
  end

  create_table "wars", force: :cascade do |t|
    t.datetime "start"
    t.datetime "end"
    t.integer "prize"
    t.integer "status", default: 0
    t.integer "time_to_answer"
    t.integer "max_unanswered_calls"
    t.integer "nb_games", default: 0
    t.integer "nb_wartimes", default: 0
    t.boolean "inc_ladder", default: false
    t.boolean "inc_tour", default: false
    t.boolean "inc_friendly", default: false
    t.boolean "inc_easy", default: false
    t.boolean "inc_normal", default: false
    t.boolean "inc_hard", default: false
    t.boolean "inc_three", default: false
    t.boolean "inc_six", default: false
    t.boolean "inc_nine", default: false
    t.datetime "created_at", precision: 6, null: false
    t.datetime "updated_at", precision: 6, null: false
  end

  add_foreign_key "active_storage_attachments", "active_storage_blobs", column: "blob_id"
  add_foreign_key "friendships", "users"
  add_foreign_key "friendships", "users", column: "friend_id"
  add_foreign_key "game_users", "games"
  add_foreign_key "game_users", "users"
  add_foreign_key "guild_users", "guilds"
  add_foreign_key "guild_users", "users"
  add_foreign_key "guild_wars", "guilds"
  add_foreign_key "guild_wars", "wars"
  add_foreign_key "room_messages", "rooms"
  add_foreign_key "room_messages", "users"
  add_foreign_key "tournament_users", "tournaments"
  add_foreign_key "tournament_users", "users"
end
