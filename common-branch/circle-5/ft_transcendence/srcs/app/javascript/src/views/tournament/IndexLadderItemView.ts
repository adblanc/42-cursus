import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import User from "src/models/User";

type Options = Backbone.ViewOptions<User> & {
  rank: number;
};

export default class IndewLadderItemView extends BaseView<User> {
  rank: number;

  constructor(options?: Options) {
    super(options);

    this.rank = options.rank;
  }

  render() {
    const template = $("#indexLadderItemTemplate").html();
    const html = Mustache.render(template, {
      ...this.model.toJSON(),
      rank: this.rank,
    });
    this.$el.html(html);

    return this;
  }
}
