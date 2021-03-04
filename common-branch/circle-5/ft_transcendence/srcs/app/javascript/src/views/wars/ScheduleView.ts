import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "../ModalView";
import War from "src/models/War";
import WarTimes from "src/collections/WarTimes";
import ItemScheduleView from "./ItemScheduleView";

export default class ScheduleView extends ModalView<War> {
	model: War;
	wartimes: WarTimes;

  constructor(options?: Backbone.ViewOptions<War>) {
	super(options);
	
	this.wartimes = this.model.get("warTimes");
  }

  render() {
    super.render();
    const template = $("#scheduleTemplate").html();
    const html = Mustache.render(template, {});
	this.$content.html(html);

	this.wartimes.forEach(function (item) {
		var itemScheduleView = new ItemScheduleView({
			model: item,
		});
		this.appendNested(itemScheduleView, "#list-schedule");
	}, this);
	
    return this;
  }
}
