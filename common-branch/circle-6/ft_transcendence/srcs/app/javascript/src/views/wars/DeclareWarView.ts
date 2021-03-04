import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "../ModalView";
import WarTimeFormView from "./WarTimeFormView";
import Guild from "src/models/Guild";
import { currentUser } from "src/models/Profile";
import War, { WarTimeDates } from "src/models/War";
import { displayError, displaySuccess } from "src/utils/toast";
import { eventBus } from "src/events/EventBus";
const flatpickr = require("flatpickr");
require("flatpickr/dist/flatpickr.css");

type Options = Backbone.ViewOptions<War> & {
  guild: Guild;
};

export default class DeclareWarView extends ModalView<War> {
  guild: Guild;
  fp_start: typeof flatpickr;
  fp_end: typeof flatpickr;
  wt_dates: WarTimeDates[];
  viewId: number;

  constructor(options?: Options) {
    super(options);

    this.guild = options.guild;
	this.wt_dates = [];
	this.viewId = 0;
	this.listenTo(eventBus, "wartime:add", this.onAddWarTime);
	this.listenTo(eventBus, "wartime:remove", this.onRemoveWarTime);
  }

  events() {
	return { ...super.events(), 
		"click #input-war-submit": "onSubmit",
		"change #inc-friendly": "onChange", };
	  }
	  
  onChange(e: JQuery.Event) {
	 e.preventDefault();
	 if( this.$("#custom").is(":visible"))
		 this.$("#custom").hide();
	 else
	 	this.$("#custom").show();
	}

	onAddWarTime(dates: WarTimeDates) { 
		this.wt_dates.push(dates);
		this.viewId++;
		var warTimeFormView = new WarTimeFormView({
			viewId: this.viewId,
		});
		this.appendNested(warTimeFormView, "#wt-schedule");
	}

	onRemoveWarTime(id: number) { 
		this.wt_dates.forEach( (item, index) => {
			if(item.id === id) this.wt_dates.splice(index,1);
		});
	}

  async onSubmit(e: JQuery.Event) {
    e.preventDefault();

    const dateTimeStart = this.fp_start.selectedDates[0];
    const dateTimeEnd = this.fp_end.selectedDates[0];
    const start = dateTimeStart;
    const end = dateTimeEnd;
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

    const initiator_id = currentUser().get("guild").get("id");
    const recipient_id = this.guild.get("id");
	const wt_dates = this.wt_dates;

    const success = await this.model.createWar(
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
      initiator_id,
      recipient_id,
	  wt_dates,
    );
    if (success) {
      this.warSaved();
    }
  }

  warSaved() {
    displaySuccess(`You declared war to ${this.guild.get("name")}`);
    this.closeModal();
	currentUser().fetch({ success: () =>
		Backbone.history.navigate(`/wars`, {
		  trigger: true,
		})
	});
  }

  dismiss = (e: JQuery.ClickEvent) => {
    if ($(e.target).closest(".flatpickr-wrapper").length === 0) {
		this.fp_start.close();
		this.fp_end.close();
    }
  };


  render() {
    super.render();
    const template = $("#warFormTemplate").html();
    const html = Mustache.render(template, this.model.toJSON());
    this.$content.html(html);

    this.fp_start = flatpickr(this.$("#input-start-date"), {
      enableTime: true,
      dateFormat: "Y-m-d H:i",
      minuteIncrement: 1,
      static: true,
      minDate: new Date(),
    }, this);
    this.fp_end = flatpickr(this.$("#input-end-date"), {
      enableTime: true,
      dateFormat: "Y-m-d H:i",
      minuteIncrement: 1,
      static: true,
      minDate: new Date(),
	});

	var warTimeFormView = new WarTimeFormView({
		viewId: this.viewId,
	});
	this.appendNested(warTimeFormView, "#wt-schedule");

	this.$content.on("click", this.dismiss);
    return this;
  }
}
