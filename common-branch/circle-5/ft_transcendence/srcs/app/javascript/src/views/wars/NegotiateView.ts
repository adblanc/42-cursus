import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "../ModalView";
import WarTimeFormView from "./WarTimeFormView";
import WarTimeFormNegoView from "./WarTimeFormNegoView";
import War, { WAR_ACTION } from "src/models/War";
import { WarTimeDates } from "src/models/War";
import WarTimes from "src/collections/WarTimes";
import { displaySuccess, displayError } from "src/utils";
import Guild from "src/models/Guild";
const flatpickr = require("flatpickr");
require("flatpickr/dist/flatpickr.css");
import moment from "moment";
import { currentUser } from "src/models/Profile";
import { eventBus } from "src/events/EventBus";

type Options = Backbone.ViewOptions<War> & {
	guild: Guild, 
 };

export default class NegotiateView extends ModalView<War> {
	guild: Guild;
	fp_start: typeof flatpickr;
	fp_end: typeof flatpickr;
	dateTimeStart: Date;
	dateTimeEnd: Date;
	wt_dates: WarTimeDates[];
	viewId: number;
	wt_change: boolean;
	warTimes: WarTimes;

  constructor(options?: Options) {
    super(options);

	this.guild = options.guild;
	this.dateTimeStart = this.model.get("start");
	this.dateTimeEnd = this.model.get("end");
	this.warTimes = this.model.get("warTimes");

	this.wt_dates = [];
	this.wt_change = false;
	this.viewId = 0;

	this.listenTo(this.guild, "change", this.render);
    this.listenTo(this.model, "change", this.render);
    this.listenTo(this.model, "add", this.render);
	this.listenTo(eventBus, "wartime:add", this.onAddWarTime);
	this.listenTo(eventBus, "wartime:remove", this.onRemoveWarTime);
  }

  events() {
    return {
	  ...super.events(),
	  "click #negotiate": "onModify",
      "click #accept": () => this.onAction("accept"),
	  "click #reject": () => this.onAction("reject"),
	  "change #input-prize": "onChange",
	  "change #input-start-date": "onDateChange",
	  "change #input-end-date": "onDateChange",
	  "change #max-calls": "onChange",
	  "change #answer-time": "onChange",
	  "change #inc-ladder": "onChange",
	  "change #inc-tour": "onChange",
	  "change #inc-friendly": "onChangeFriendly",
	  "change #inc-easy": "onChange",
	  "change #inc-normal": "onChange",
	  "change #inc-hard": "onChange",
	  "change #three-points": "onChange",
	  "change #six-points": "onChange",
	  "change #nine-points": "onChange",
    };
  }

  onAddWarTime(dates: WarTimeDates) { 
	this.wt_dates.push(dates);
	this.viewId++;
	var warTimeFormView = new WarTimeFormView({
		viewId: this.viewId,
	});
	this.appendNested(warTimeFormView, "#wt-schedule");
	this.wt_change = true;
	this.changeButtons();
}

  onRemoveWarTime(id: number) { 
	this.wt_dates.forEach( (item, index) => {
		if(item.id === id) this.wt_dates.splice(index,1);
	});
	this.wt_change = true;
	this.changeButtons();
  }

  changeButtons() {
	this.$("#accept").removeClass("btn-nego");
	this.$("#accept").addClass("btn-nego-disabled");
	this.$("#negotiate").removeClass("btn-nego-disabled");
	this.$("#negotiate").addClass("btn-nego");
  }

  onChange(e: JQuery.Event) {
	e.preventDefault();
	this.changeButtons();
  }

  onChangeFriendly(e: JQuery.Event) {
	e.preventDefault();
	this.changeButtons();
	if( this.$("#custom").is(":visible")) 
		 this.$("#custom").hide();
	else
	 	this.$("#custom").show();
  }

  onDateChange(e: Event) {
	e.preventDefault();
	this.changeButtons();
	if ($(e.target).is("#input-start-date"))
		this.dateTimeStart = this.fp_start.selectedDates[0];
	if ($(e.target).is("#input-end-date"))
 		this.dateTimeEnd = this.fp_end.selectedDates[0];
  }

  async onAction(action: WAR_ACTION) {
    const success = await this.model.manageAction(
      action,
    );

    if (success) {
      this.actionSaved(action);
    }
  }

  actionSaved(action: WAR_ACTION) {
    displaySuccess(
		`You have successfully ${action}ed the proposition of war.`
	);
	this.guild.fetch();
	currentUser().fetch();
    this.closeModal();
  }

  async onModify(e: JQuery.Event) {
	e.preventDefault();
	const start = this.dateTimeStart; 
	const end = this.dateTimeEnd;
	const prize = this.$("#input-prize").val() as string;
	const answer_time = this.$("#answer-time").val() as string;
	const max_calls = this.$("#max-calls").val() as string;
	const inc_ladder= this.$("#inc-ladder").is(":checked");
	const inc_tour= this.$("#inc-tour").is(":checked");
	const inc_friendly = this.$("#inc-friendly").is(":checked");
	const inc_easy = this.$("#inc-easy").is(":checked");
	const inc_normal = this.$("#inc-normal").is(":checked");
	const inc_hard = this.$("#inc-hard").is(":checked");
	const inc_three = this.$("#three-points").is(":checked");
	const inc_six = this.$("#six-points").is(":checked");
	const inc_nine = this.$("#nine-points").is(":checked");

	const wt_dates = this.wt_dates;
	const wt_change = this.wt_change;

	/*if (parseInt(prize) > this.model.get("warOpponent").get("points") || parseInt(prize) > this.guild.get("points")) {
		displayError("One or both guilds cannot wager that many points");
		return;
	}*/

    const success = await this.model.modifyWar(
		start,
		end,
		prize,
		answer_time,
		max_calls,
		inc_ladder,
		inc_tour,
		inc_friendly,
		inc_easy,
		inc_normal,
		inc_hard,
		inc_three,
		inc_six,
		inc_nine,
		wt_dates,
		wt_change,
	  );

    if (success) {
      displaySuccess("You have successfully proposed new terms.");
      this.closeModal();
	  this.model.fetch();
	  this.guild.fetch();
	  currentUser().fetch();
    }
  }

  dismiss = (e: JQuery.ClickEvent) => {
    if ($(e.target).closest(".flatpickr-wrapper").length === 0) {
		this.fp_start.close();
		this.fp_end.close();
    }
  };

  render() {
	const model = {
		...this.model.toJSON(),
		start: moment(this.model.get("start")).format(
			"MMM Do YY, h:mm a"
		),
		end: moment(this.model.get("end")).format(
		  "MMM Do YY, h:mm a"
		)
	};

    super.render();
    const template = $("#negoTemplate").html();
    const html = Mustache.render(template, {
		war: model,
		img: this.model.get("warOpponent").get("img_url"),
		name: this.model.get("warOpponent").get("name"),
		url: `/guild/${this.model.get("warOpponent").get("id")}`,	
	});
	this.$content.html(html);
	
	const $ranked = this.$("#ranked");
    const $member = this.$("#member");

	if(currentUser().get("guild_role") == "Member") {
		$member.show();
		this.$("#input-start-date").prop( "disabled", true );
		this.$("#input-end-date").prop( "disabled", true );
		this.$("#input-prize").prop( "disabled", true );
	} else {
		$ranked.show();
	}

	this.fp_start = flatpickr(this.$("#input-start-date"), {
		enableTime: true,
		dateFormat: "Y-m-d H:i",
		minuteIncrement: 1,
		static: true,
		minDate: new Date(),
	});
	this.fp_end = flatpickr(this.$("#input-end-date"), {
		enableTime: true,
		dateFormat: "Y-m-d H:i",
		minuteIncrement: 1,
		static: true,
		minDate: new Date(),
	});

	if (this.model.get("inc_ladder"))
		this.$("#inc-ladder").attr( 'checked', 'checked' );
	if (this.model.get("inc_tour"))
		this.$("#inc-tour").attr( 'checked', 'checked' );
	if (this.model.get("inc_friendly")) {
		this.$("#inc-friendly").attr( 'checked', 'checked' );
		this.$("#custom").show();
	}
	if (this.model.get("inc_easy"))
		this.$("#inc-easy").attr( 'checked', 'checked' );
	if (this.model.get("inc_normal"))
		this.$("#inc-normal").attr( 'checked', 'checked' );
	if (this.model.get("inc_hard"))
		this.$("#inc-hard").attr( 'checked', 'checked' );
	if (this.model.get("inc_three"))
		this.$("#three-points").attr( 'checked', 'checked' );
	if (this.model.get("inc_six"))
		this.$("#six-points").attr( 'checked', 'checked' );
	if (this.model.get("inc_nine"))
		this.$("#nine-points").attr( 'checked', 'checked' );

	this.$content.on("click", this.dismiss);

	this.warTimes.forEach(function (item) {
		let id = this.viewId;
		let start = item.get("start");
		let end = item.get("end");
		let dates: WarTimeDates = {
			id, start, end,
		};
		this.wt_dates.push(dates);
		var warTimeFormNegoView = new WarTimeFormNegoView({
			viewId: this.viewId,
			wartime: item,
		});
		this.appendNested(warTimeFormNegoView, "#wt-schedule");
		this.viewId++;
	}, this);

	var warTimeFormView = new WarTimeFormView({
		viewId: this.viewId,
	});
	this.appendNested(warTimeFormView, "#wt-schedule");

    return this;
  }
}
