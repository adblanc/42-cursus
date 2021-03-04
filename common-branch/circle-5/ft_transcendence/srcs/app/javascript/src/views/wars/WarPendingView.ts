import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import Wars from "src/collections/Wars";
import Guild from "src/models/Guild";
import ItemPendingView from "./ItemPendingView";

type Options = Backbone.ViewOptions & { collection: Wars, guild: Guild};

export default class WarPendingView extends BaseView {
  collection: Wars;
  guild: Guild;
  constructor(options?: Options) {
	super(options);
	
	this.collection = options.collection;
	this.guild = options.guild;

    this.listenTo(this.collection, "reset", this.render);
	this.listenTo(this.collection, "change", this.render);
	this.listenTo(this.collection, "remove", this.render);
  }

  render() {
    const template = $("#pendingWarsTemplate").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);

	const $element = this.$("#listing-pending");

    this.collection.forEach(function (item) {
      var itemView = new ItemPendingView({
		model: item,
		guild: this.guild,
      });
      $element.append(itemView.render().el);
    }, this);

    return this;
  }
}