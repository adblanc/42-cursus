import Mustache from "mustache";
import Backbone from "backbone";
import BaseView from "src/lib/BaseView";
import IndexLadderItemView from "./IndexLadderItemView";
import { currentUser } from "src/models/Profile";
import RankedUsers from "src/collections/RankedUsers";

export default class IndexLadderView extends BaseView {
  players: RankedUsers;

  constructor(options?: Backbone.ViewOptions) {
    super(options);

    this.players = new RankedUsers();
    this.players.fetch();
    this.players.sort();

    this.listenTo(this.players, "change", this.render);
    this.listenTo(this.players, "update", this.render);
    this.listenTo(this.players, "sort", this.render);
  }

  render() {
    const template = $("#indexLadderTemplate").html();
    const html = Mustache.render(template, currentUser().toJSON());
    this.$el.html(html);

    const $element = this.$("#list");

    this.players.slice(0, 5).forEach((item) => {
      var itemView = new IndexLadderItemView({
        model: item,
        rank: this.players.indexOf(item) + 1,
      });
      $element.append(itemView.render().el);
    });

    return this;
  }
}
