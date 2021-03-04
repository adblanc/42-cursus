class EndWarJob < ApplicationJob
	queue_as :default

	def perform(war)
	  return if not war.started?
	  war.update(status: :ended)
	  if war.guilds.first.war_points(war) > war.guilds.second.war_points(war)
		war.guilds.first.win_score(war.prize)
		war.guilds.second.lose_score(war.prize)
		@winner = war.guilds.first
		self.send_winner(war, @winner)
      elsif war.guilds.first.war_points(war) < war.guilds.second.war_points(war)
		war.guilds.second.win_score(war.prize)
		war.guilds.first.lose_score(war.prize)
		@winner = war.guilds.second
		self.send_winner(war, @winner)
	  else
		war.guilds.first.win_score(war.prize / 2)
		war.guilds.second.win_score(war.prize / 2)
		self.send_tie(war)
	  end
	end

	def send_winner(war, winner)
		war.guilds.each do |guild|
			guild.members.each do |member|
				member.send_notification("War with #{war.opponent(guild).name} just ended ! #{winner.name} won #{war.prize} points!", "/wars", "wars")
			end
		end
	end

	def send_tie(war)
		war.guilds.each do |guild|
			guild.members.each do |member|
				member.send_notification("War with #{war.opponent(guild).name} just ended ! It's a tie! Prize was split into two!", "/wars", "wars")
			end
		end
	end
end
