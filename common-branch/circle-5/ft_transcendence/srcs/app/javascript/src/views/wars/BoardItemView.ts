import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import War from "src/models/War";
import moment from "moment";

type Options = Backbone.ViewOptions & { model: War };

export default class BoardItemView extends BaseView {
  model: War;

  constructor(options?: Options) {
    super(options);
  }

  render() {
	const war = {
		...this.model.toJSON(),
		end: moment(this.model.get("end")).fromNow(),
	};

    const template = $("#itemWarTemplate").html();
    const html = Mustache.render(template, war);
	this.$el.html(html);
	

    return this;
  }
}