import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import War from "src/models/War";
import Guild from "src/models/Guild";
import moment from "moment";
import ScheduleView from "./ScheduleView";

type Options = Backbone.ViewOptions & { war: War, guild: Guild};

export default class WarWaitingView extends BaseView {
	war: War;
	guild: Guild;
	opponent: Guild;

  constructor(options?: Options) {
    super(options);

	this.war = options.war;
	this.guild = options.guild;

	this.listenTo(this.war, "change", this.render);
  }

  events() {
    return {
	  "click #wt-schedule": "onScheduleClicked",
    };
  }

  onScheduleClicked() {
	const scheduleView = new ScheduleView({
		model: this.war,
	});
	scheduleView.render();
  }

  render() {
	const war = {
		...this.war.toJSON(),
		start: moment(this.war.get("start")).format(
			"MMM Do YY, h:mm a"
		),
		end: moment(this.war.get("end")).format(
		  "MMM Do YY, h:mm a"
		)
	};

	const template = $("#warWaitingTemplate").html();
	const html = Mustache.render(template, { 
		war: war,
		img: this.guild.get("warOpponent").get("img_url"),
		name: this.guild.get("warOpponent").get("name"),
		url: `/guild/${this.guild.get("warOpponent").get("id")}`,
	});
	this.$el.html(html);

	if (this.war.get("max_unanswered_calls"))
		this.$("#max-calls").show();

    return this;
  }
}