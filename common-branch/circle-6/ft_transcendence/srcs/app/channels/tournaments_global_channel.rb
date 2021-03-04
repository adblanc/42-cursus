class TournamentsGlobalChannel < ApplicationCable::Channel
	def subscribed
		stream_from "tournaments_global"
	end

	def unsubscribed
	end
end
