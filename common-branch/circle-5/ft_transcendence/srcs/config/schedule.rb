set :output, '/app/log/cron.log'
set :environment, ENV['RAILS_ENV']

every '0 12 * * 1' do
	runner "Tournament.cron_create"
end
