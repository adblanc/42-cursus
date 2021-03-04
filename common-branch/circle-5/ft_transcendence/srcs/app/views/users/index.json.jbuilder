json.array! @users do |user|
  json.partial! "users/userSnippet", user: user
end