json.partial! "users/user", user: user
json.statUser do
  json.achievement user.achievement?
  json.number_victory user.number_victory
  json.number_loss user.number_loss
  json.ladder_rank user.ladder_rank
  json.bronze_medal user.bronze_medal?
  json.silver_medal user.silver_medal?
  json.gold_medal user.gold_medal?
  json.best_guild user.best_guild?
  json.high_rank user.high_rank?
  json.war_won user.war_won?
  json.lucky_man user.lucky_man?
end
