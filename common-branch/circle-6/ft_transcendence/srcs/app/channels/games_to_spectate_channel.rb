class GamesToSpectateChannel < ApplicationCable::Channel
	def subscribed
		@channel = "games_to_spectate";

		stream_from @channel
	end

	def unsubscribed
	end

	private

end
