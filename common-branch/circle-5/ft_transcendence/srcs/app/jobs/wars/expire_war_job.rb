class ExpireWarJob < ApplicationJob
	queue_as :default

	def perform(war)
	  if not war.started?
		war.initiator.members.each do | member |
			member.send_notification("#{war.opponent(war.initiator).name} never answered you war declaration!", "/wars", "wars")
		end
		war.opponent(war.initiator).members.each do | member |
			member.send_notification("Your Guild has not answered #{war.initiator.name}'s War declaration!", "/wars", "wars")
		end
		war.destroy
	  end
	end
end
