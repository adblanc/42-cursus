import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import War from "src/models/War";
import Guild from "src/models/Guild";
import NegotiateView from "./NegotiateView";

type Options = Backbone.ViewOptions & { model: War, guild: Guild};

export default class ItemPendingView extends BaseView {
  model: War;
  guild: Guild;

  constructor(options?: Options) {
    super(options);

	this.model = options.model;
	this.guild = options.guild;

	this.listenTo(this.model, "change", this.render);
  }

  events() {
    return {
      "click #see-btn": "onSeeClicked",
    };
  }

  onSeeClicked() {
	const negotiateView = new NegotiateView({
		model: this.model,
		guild: this.guild,
	  });
  
	  negotiateView.render();
  }

  render() {
    const template = $("#pendingWarTemplate").html();
	const html = Mustache.render(template, {
		img: this.model.get("warOpponent").get("img_url"),
		name: this.model.get("warOpponent").get("name"),
		url: `/guild/${this.model.get("warOpponent").get("id")}`,
	});
	this.$el.html(html);
	

    return this;
  }
}