class StartWarTimeJob < ApplicationJob
	queue_as :default

	def perform(wartime, war)
	  wartime.update(status: :active)
	  war.guilds.each do |guild|
		guild.members.each do |member|
			member.send_notification("WarTime with #{war.opponent(guild).name} just started !", "/wars", "wars")
		end
	  end
	  EndWarTimeJob.set(wait_until: wartime.end).perform_later(wartime, war)
	  war.increment!(:nb_wartimes, 1)
	end

end
