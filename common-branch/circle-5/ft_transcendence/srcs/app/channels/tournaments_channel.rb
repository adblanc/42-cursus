class TournamentsChannel < ApplicationCable::Channel
	def subscribed
		stream_from "tournament_#{params[:id]}"
	end

	def unsubscribed
	end
end
