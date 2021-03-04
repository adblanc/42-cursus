import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import ChallengeView from "./ChallengeView";
import AcceptChallengeView from "./AcceptChallengeView";
import War from "src/models/War";
import Game from "src/models/Game";
import WarTime from "src/models/WarTime";
import moment from "moment";
import { currentUser } from "src/models/Profile";
import { displayError } from "src/utils";

type Options = Backbone.ViewOptions & { war: War};

export default class ActiveWarTimeView extends BaseView {
	war: War;
	warTime: WarTime;
	time_left: string;

  constructor(options?: Options) {
    super(options);

	this.war = options.war;
	this.warTime = this.war.get("activeWarTime");

	this.listenTo(this.war, "change", this.render);
	this.listenTo(this.warTime, "change", this.render);
	
  }

  events() {
    return {
	  "click #challenge-btn": "onChallengeClicked",
	  "click #accept-btn": "onAcceptClicked",
    };
  }

  onChallengeClicked() {
	var now = moment().toDate().getTime();
	var end = moment(this.warTime.get("end"));
	var diff = end.diff(now, 'minutes');
	if (diff < parseInt(this.warTime.get("time_to_answer"), 10)) {
		displayError('War Time will be over soon. No time left to challenge your opponent.');
		return;
	}

	const game = new Game();
	const challengeView = new ChallengeView({
		model: game,
		warTime: this.warTime,
	});
  
	challengeView.render();
  }

  onAcceptClicked() {
	const acceptChallengeView = new AcceptChallengeView({
		model: this.warTime.get("pendingGame"),
	});
  
	acceptChallengeView.render();
  }

  render() {
	if (this.warTime.get("pendingGame")) {
		var date = moment(this.warTime.get("pendingGame").get("created_at")).add(parseInt(this.war.get("time_to_answer"), 10), 'minutes');
		this.time_left = moment(date).fromNow();
	}

	const warTime = {
		...this.warTime.toJSON(),
		end: moment(this.warTime.get("end")).format(
		  "MMM Do YY, h:mm a"
		),
		time_left: this.time_left,
	};

    const template = $("#activeWarTimeTemplate").html();
    const html = Mustache.render(template, warTime);
	this.$el.html(html);

	if (this.warTime.get("pendingGame")) {
		if (this.warTime.get("pendingGameInitiator").get("id") == currentUser().get("id"))
			this.$("#wait").show();
		else if (this.warTime.get("pendingGameGuildInitiator").get("id") == currentUser().get("guild").get("id")) 
			this.$("#unavailable").show();
		else
			this.$("#accept").show();
	}
	else if (this.warTime.get("activeGame")) {
		this.$("#in-game").show();
	}
	else { 
		this.$("#challenge").show();
	}
	
    return this;
  }
}
