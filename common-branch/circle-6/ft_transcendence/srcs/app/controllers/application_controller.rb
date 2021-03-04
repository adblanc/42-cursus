class ApplicationController < ActionController::Base
	helper_method :current_user
	def index
	end

	def current_user
			token = bearer_token
			return nil unless token
			payload = TokiToki.decode(token)
			@current_user ||= User.find_by_login(payload[0]['sub'])
			if (@current_user.is_banned?)
				return nil
			else
				@current_user
			end
		rescue JWT::ExpiredSignature
			return nil
	  end

	  def logged_in?
		current_user != nil
	  end

	  def authenticate_user!
		head :unauthorized unless logged_in?
	  end


	  private

	  def bearer_token
		pattern = /^Bearer /
		header  = request.headers['Authorization']
		header.gsub(pattern, '') if header && header.match(pattern)
	  end
end
