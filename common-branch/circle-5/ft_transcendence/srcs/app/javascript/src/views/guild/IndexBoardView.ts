import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import Guilds from "src/collections/Guilds";
import ItemView from "./ItemView";

export default class IndexBoardView extends BaseView {
  collection: Guilds;
  itemView: Backbone.View;

  constructor(options?: Backbone.ViewOptions) {
    super(options);

    this.collection = new Guilds();
    this.listenTo(this.collection, "reset", this.render);
    this.listenTo(this.collection, "change", this.render);
    this.listenTo(this.collection, "sort", this.render);
    this.collection.fetch();
    this.collection.sort();
  }

  render() {
    const template = $("#indexBoardTemplate").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);

    const $element = this.$("#list");

    this.collection.slice(0, 5).forEach((item) => {
      var itemView = new ItemView({
        model: item,
        maximumPoints: this.collection.maximumPoints,
      });
      $element.append(itemView.render().el);
    });

    return this;
  }
}
