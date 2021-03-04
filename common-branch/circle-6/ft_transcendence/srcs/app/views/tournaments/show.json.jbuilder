json.partial! "tournaments/tournament", tournament: @tournament
json.user_status @tournament.user_status(current_user)