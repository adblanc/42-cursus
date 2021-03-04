import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import WarTime from "src/models/WarTime";
import moment from "moment";

export default class ItemScheduleView extends BaseView<WarTime> {

  constructor(options?: Backbone.ViewOptions<WarTime>) {
    super(options);
  }


  render() {
	const model = {
		...this.model.toJSON(),
		start: moment(this.model.get("start")).format(
			"MMM Do, h:mm a"
		),
		end: moment(this.model.get("end")).format(
		  "MMM Do, h:mm a"
		),
	};

    const template = $("#itemScheduleTemplate").html();
	const html = Mustache.render(template, model);
	this.$el.html(html);
	

    return this;
  }
}