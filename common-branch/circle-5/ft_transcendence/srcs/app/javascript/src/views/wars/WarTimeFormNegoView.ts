import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
const flatpickr = require("flatpickr");
import { eventBus } from "src/events/EventBus";
import WarTime from "src/models/WarTime";
require("flatpickr/dist/flatpickr.css");
import moment from "moment";

type Options = Backbone.ViewOptions & {
	viewId: number;
	wartime: WarTime;
  };

export default class WarTimeFormNegoView extends BaseView{
  viewId: number;
  wartime: WarTime;

  constructor(options?: Options) {
    super(options);

	this.viewId = options.viewId;
	this.wartime = options.wartime;
  }

  events() {
	return {
		"click .remove-war-time": "onRemoveWT"
	};
  }
	  
	onRemoveWT(e: JQuery.Event) {
		e.preventDefault();
		eventBus.trigger("wartime:remove", this.viewId);
		this.close();
	}


  render() {
	const wartime = {
		...this.wartime.toJSON(),
		start: moment(this.wartime.get("start")).format(
			"MMM Do, h:mm a"
		),
		end: moment(this.wartime.get("end")).format(
		  "MMM Do, h:mm a"
		)
	};

    const template = $("#warTimesNegoFormTemplate").html();
    const html = Mustache.render(template, wartime);
    this.$el.html(html);

    return this;
  }
}
