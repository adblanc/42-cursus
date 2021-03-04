json.extract! war, :id, :start, :end, :prize, :status, :time_to_answer, :max_unanswered_calls, :nb_games, :nb_wartimes, :created_at, :updated_at
json.atWarTime war.atWarTime?
if war.activeWarTime
	json.activeWarTime do
		json.id war.activeWarTime.id
		json.start war.activeWarTime.start
		json.end war.activeWarTime.end
		json.time_to_answer war.activeWarTime.time_to_answer
		json.max_unanswered_calls war.activeWarTime.max_unanswered_calls
		json.unanswered_calls war.activeWarTime.unanswered_calls
	end
else
	json.activeWarTime nil
end
json.partial! "wars/warinclude", war: war
json.warTimes do
	json.array! war.war_times do |war_time|
		json.partial! "wars/war_time", war_time: war_time
	end
end