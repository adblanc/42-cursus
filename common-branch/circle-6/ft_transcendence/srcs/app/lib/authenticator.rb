class Authenticator
	def initialize(client = OAuth2::Client.new(ENV['CLIENT_ID'], ENV['CLIENT_SECRET'], site: "https://api.intra.42.fr"))
	  @client = client
	end

	def auth42(code)
	user_info_resp = fetch_42_user_info(code)
	{
		issuer: ENV['CLIENT_URL'],
		login: user_info_resp['login'],
		name: user_info_resp['displayname'],
		avatar_url: user_info_resp['image_url'],
		email: user_info_resp['email']
	}
	end

	private

	def fetch_42_user_info(code)
		token = @client.auth_code.get_token(code, :redirect_uri => ENV['CLIENT_REDIRECT'])
		token.get("/v2/me").parsed
	end
  end
