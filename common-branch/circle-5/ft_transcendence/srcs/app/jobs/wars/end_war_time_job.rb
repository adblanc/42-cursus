class EndWarTimeJob < ApplicationJob
	queue_as :default

	def perform(warTime, war)
	  return if warTime.inactive?
	  warTime.update(status: :inactive)
	  war.guilds.each do |guild|
		guild.members.each do |member|
			member.send_notification("WarTime with #{war.opponent(guild).name} just ended !", "/wars", "wars")
		end
	  end
	end

end
