import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import Wars from "src/collections/Wars";
import War from "src/models/War";
import BoardItemView from "./BoardItemView";
import { eventBus } from "src/events/EventBus";

type Options = Backbone.ViewOptions & { collection: Wars };

export default class WarBoardView extends BaseView {
  collection: Wars;
  max: number;
  count: number;

  constructor(options?: Options) {
    super(options);

    this.max = 5;

    this.collection = new Wars();
    this.collection.fetch();

    this.listenTo(this.collection, "add", this.render);
    this.listenTo(this.collection, "update", this.render);
    this.listenTo(eventBus, "wars:update", this.onUpdate);
  }

  onUpdate() {
    this.collection.fetch();
  }

  renderWar(war: War) {
    var itemWarView = new BoardItemView({
      model: war,
    });
    this.$("#listing").append(itemWarView.render().el);
  }

  onLoadMore() {
    var wars = this.collection.models.slice(this.count, this.count + this.max);
    if (wars.length) {
      wars.forEach(function (item) {
        this.renderWar(item);
      }, this);
      this.count += wars.length;
    }
    if (this.count == this.collection.length) {
      this.$("#load-more").hide();
    }
  }

  render() {
    const template = $("#warBoardTemplate").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);

    var wars = this.collection.first(this.max);

    if (wars.length == 0) {
      this.$("#none").show();
    }

    wars.forEach(function (item) {
      this.renderWar(item);
    }, this);
    this.count = wars.length;
    if (this.count == this.collection.length) {
      this.$("#load-more").hide();
    }

    return this;
  }
}
