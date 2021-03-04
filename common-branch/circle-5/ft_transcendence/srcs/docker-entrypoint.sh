#!/bin/bash

yarn install
rm -f tmp/pids/server.pid

function launch_cron() {
	rails runner 'Sidekiq.redis { |conn| conn.flushdb }'
	cp ./base.rb /usr/local/bundle/gems/actionpack-6.0.3.4/lib/action_controller/base.rb
	whenever --update-crontab
	crond
}

if [ "$RAILS_ENV" = "production" ]
then
	RAILS_ENV=production DISABLE_DATABASE_ENVIRONMENT_CHECK=1 rails db:drop db:create db:migrate db:seed
	launch_cron
	bundle exec rails webpacker:compile
	./bin/rails s -b 0.0.0.0 -e production
else
	rails db:drop db:create db:migrate db:seed
	launch_cron
	./bin/webpack-dev-server & bin/rails s -b 0.0.0.0
fi
