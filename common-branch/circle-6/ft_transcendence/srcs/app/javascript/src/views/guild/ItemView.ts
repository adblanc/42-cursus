import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import Guild from "src/models/Guild";

type Options = Backbone.ViewOptions<Guild> & {
  maximumPoints: number;
};

export default class ItemView extends BaseView<Guild> {
  maxPoints: number;

  constructor(options?: Options) {
    super(options);

    this.model = options.model;
    this.maxPoints = options.maximumPoints;
  }

  render() {
    const template = $("#itemTemplate").html();

    const html = Mustache.render(template, {
      ...this.model.toJSON(),
      pointsPercentage: this.model.pointsPercentage(this.maxPoints),
    });
    this.$el.html(html);

    return this;
  }
}
