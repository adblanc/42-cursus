json.array! @tournaments do |tournament|
  json.partial! "tournaments/tournament", tournament: tournament
end