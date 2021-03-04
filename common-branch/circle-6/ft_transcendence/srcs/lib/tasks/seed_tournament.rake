namespace :seed_tournament do
  desc "usage: rake seed_tournament:seed[id]"
  task :seed, [:id] => [:environment] do |task, args|
	tournament = Tournament.find_by_id(args[:id])
	tournament.users.push(User.find(1))
	game_seed_for_test(tournament, User.find(1))
	tournament.users.push(User.find(2))
	game_seed_for_test(tournament, User.find(2))
	tournament.users.push(User.find(3))
	game_seed_for_test(tournament, User.find(3))
	tournament.users.push(User.find(4))
	game_seed_for_test(tournament, User.find(4))
	tournament.users.push(User.find(5))
	game_seed_for_test(tournament, User.find(5))
	tournament.users.push(User.find(6))
	game_seed_for_test(tournament, User.find(6))
	tournament.users.push(User.find(7))
	game_seed_for_test(tournament, User.find(7))
	tournament.users.push(User.find(8))
	game_seed_for_test(tournament, User.find(8))
  end

end

def game_seed_for_test(tournament, user)
	tournament.games.quarter.each do | game |
		if game.users.count < 2
			game.users.push(user)
			game.game_users.where(user: user).update(status: :pending)
			return
		end
	end
  end
