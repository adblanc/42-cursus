class StartRegistrationJob < ApplicationJob
	queue_as :default

	def perform(tournament)
	  return if not tournament.pending?
	  tournament.update(status: :registration)
	  ActionCable.server.broadcast("tournament_#{tournament.id}", {})
	  User.all.each do |user|
		user.send_notification("Registrations are open for #{tournament.name} tournament !", "tournaments/#{tournament.id}", "tournaments")
	  end
	  EndRegistrationJob.set(wait_until: tournament.registration_end).perform_later(tournament)
	end
end
