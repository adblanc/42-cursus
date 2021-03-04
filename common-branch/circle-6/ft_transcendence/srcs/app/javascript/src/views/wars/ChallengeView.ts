import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "../ModalView";
import War from "src/models/War";
import Game from "src/models/Game";
import WarTime from "src/models/WarTime";
import { displaySuccess, displayError } from "src/utils";
import { currentUser } from "src/models/Profile";

type Options = Backbone.ViewOptions<Game> & {
	warTime: WarTime;
};

export default class ChallengeView extends ModalView<Game> {
	warTime: WarTime;

  constructor(options?: Options) {
	super(options);
	
	this.warTime = options.warTime;
  }

  events() {
    return { ...super.events(), "click #input-challenge-submit": "onSubmit" };
  }

  async onSubmit(e: JQuery.Event) {
	e.preventDefault();

	var level = this.$("#level").val() as string;
	var goal = this.$("#goal").val() as number;
	var game_type = "war_time";
	var warTimeId = this.warTime.get("id");
  
	const success = await this.model.challengeWT(
		level,
		goal,
		game_type,
		warTimeId,
	);
	if (success) {
		this.gameSaved();
	}
  }

  gameSaved() {
    this.closeModal();
    displaySuccess("Your challenge has been sent to the opponent guild...");
	currentUser().fetch();
	this.model.fetch();
	this.model.createChannelConsumer();
	Backbone.history.navigate(`/play`, {
		trigger: true,
	});
  }


  render() {
    super.render();
    const template = $("#challengeTemplate").html();
    const html = Mustache.render(template, this.warTime.toJSON());
	this.$content.html(html);

	if (this.warTime.get("max_unanswered_calls"))
		this.$("#max-calls").show();
	
    return this;
  }
}
