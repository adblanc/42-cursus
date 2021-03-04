import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import War, { WarTimeDates } from "src/models/War";
const flatpickr = require("flatpickr");
import { eventBus } from "src/events/EventBus";
import { displayError, displaySuccess } from "src/utils/toast";
require("flatpickr/dist/flatpickr.css");

type Options = Backbone.ViewOptions & {
	viewId: number;
  };

export default class WarTimeFormView extends BaseView{
  fp_start: typeof flatpickr;
  fp_end: typeof flatpickr;
  viewId: number;

  constructor(options?: Options) {
    super(options);

	this.viewId = options.viewId;
  }

  events() {
	return {
		"click #add-war-time": "onAddWT",
		"click .remove-war-time": "onRemoveWT"
	};
  }
	  
	onAddWT(e: JQuery.Event) {
		e.preventDefault();
		const dateTimeStart = this.fp_start.selectedDates[0];
		const dateTimeEnd = this.fp_end.selectedDates[0];

		if (!dateTimeStart || !dateTimeEnd) {
			displayError(`Fill in the dates to add war time`);
			return;
		}

		const start = dateTimeStart;
		const end = dateTimeEnd;
		const id = this.viewId;
		let dates: WarTimeDates = {
			id, start, end
		};
		eventBus.trigger("wartime:add", dates);
		this.$('#add-war-time').hide();
		this.$('.remove-war-time').show();
		this.$("#wt-start-date").addClass("timepickr-disabled");
		this.$("#wt-end-date").addClass("timepickr-disabled");

	}

	onRemoveWT(e: JQuery.Event) {
		e.preventDefault();
		eventBus.trigger("wartime:remove", this.viewId);
		this.close();
	}


  dismiss = (e: JQuery.ClickEvent) => {
    if ($(e.target).closest(".flatpickr-wrapper").length === 0) {
		this.fp_start.close();
		this.fp_end.close();
    }
  };

  render() {
    const template = $("#warTimesFormTemplate").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);

    this.fp_start = flatpickr(this.$("#wt-start-date"), {
      enableTime: true,
      dateFormat: "Y-m-d H:i",
      minuteIncrement: 1,
      static: true,
      minDate: new Date(),
    }, this);
    this.fp_end = flatpickr(this.$("#wt-end-date"), {
      enableTime: true,
      dateFormat: "Y-m-d H:i",
      minuteIncrement: 1,
      static: true,
      minDate: new Date(),
	});

	this.$el.on("click", this.dismiss);
    return this;
  }
}
