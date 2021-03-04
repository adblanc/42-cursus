# This file should contain all the record creation needed to seed the database with its default values.
# The data can then be loaded with the rails db:seed command (or created alongside the database with db:setup).
#
# Examples:
#
#   movies = Movie.create([{ name: 'Star Wars' }, { name: 'Lord of the Rings' }])
#   Character.create(name: 'Luke', movie: movies.first)

bob = User.create(name: "bob", login: "bob");
bill = User.create(name: "bill", login: "bill", contribution: 10);
ben = User.create(name: "ben", login: "ben", contribution: 20);
boule = User.create(name: "boule", login: "boule", contribution: 30);
babar = User.create(name: "babar", login: "babar", contribution: 40);
billy = User.create(name: "billy", login: "billy", contribution: 30);
jeff = User.create(name: "jeff", login: "jeff", contribution: 20);
john = User.create(name: "john", login: "john", contribution: 10);
jack = User.create(name: "jack", login: "jack", contribution: 0);

User.all.each do |user|
	user.update_attributes(:otp_secret_key => ROTP::Base32.random)
end

bob.avatar.attach(
	io: URI.open("https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQ1pEVYSLDyjch3zZYccCMgguA2zDSLyVP8EPrOb_2DSPNuV60si_Qju-Ll9fnDvfzEXcDEGDTD&usqp=CAc"),
	filename: "bob.png",
	"content_type": "image/png",
)

bill.avatar.attach(
	io: URI.open("https://upload.wikimedia.org/wikipedia/commons/thumb/f/fb/Hotdog_-_Evan_Swigart.jpg/1024px-Hotdog_-_Evan_Swigart.jpg"),
	filename: "bill.png",
	"content_type": "image/png",
)

ben.avatar.attach(
	io: URI.open("https://images.theconversation.com/files/273610/original/file-20190509-183106-1fqctm9.jpg?ixlib=rb-1.1.0&rect=9%2C53%2C3254%2C2384&q=45&auto=format&w=926&fit=clip"),
	filename: "ben.png",
	"content_type": "image/png",
)

guild1 = Guild.create(name: 'The Best Guild', ang: "TBG", points: 30)
guild2 = Guild.create(name: 'The Doom', ang: "TDM", points: 70)
guild3 = Guild.create(name: 'The Blabla', ang: "BLB", points: 30)
guild4 = Guild.create(name: 'The Pandemic', ang: "BLB", points: 30)
guild5 = Guild.create(name: 'The Symetry', ang: "BLB", points: 0)

guild1.img.attach(
	io: URI.open("https://i.pinimg.com/originals/1a/27/ff/1a27ff81c19e1c10583ea970b0f3827f.jpg"),
	filename: "guild1.jpg",
	"content_type": "image/jpg",
)

guild2.img.attach(
	io: URI.open("https://www.picclickimg.com/d/l400/pict/263841790404_/Harry-Potter-Hogwarts-RAVENCLAW-QUIDDITCH-TEAM-CAPTAIN-Pin.jpg"),
	filename: "guild2.jpg",
	"content_type": "image/jpg",
)

guild1.members << bill
bill.add_role(:owner, guild1)
guild1.members << ben
guild2.members << boule
boule.add_role(:owner, guild2)
guild2.members << babar
guild3.members << billy
billy.add_role(:owner, guild3)
guild4.members << jeff
guild4.members << john
john.add_role(:owner, guild4)
guild5.members << jack
jack.add_role(:owner, guild5)

john.add_role :master
