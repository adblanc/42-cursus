class StartWarJob < ApplicationJob
	queue_as :default

	def perform(war)
	  return if not war.confirmed?
	  war.update(status: :started)
	  war.guilds.each do |guild|
		guild.members.each do |member|
			member.send_notification("War with #{war.opponent(guild).name} just started !", "/wars", "wars")
		end
	  end
	end
end
