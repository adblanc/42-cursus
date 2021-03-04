import Backbone from "backbone";
import Mustache from "mustache";
import moment from "moment";
import BaseView from "../../lib/BaseView";
import Game from "src/models/Game";
import User from "src/models/User";

type Options = Backbone.ViewOptions & { model: Game; user: User };

export default class HistoryItemView extends BaseView {
  model: Game;
  user: User;

  constructor(options?: Options) {
    super(options);
    this.model = options.model;
    this.user = options.user;
  }

  render() {
    const opponent = this.model
      .get("players")
      .find((u) => u.get("id") !== this.user.get("id"));
    const user = this.model
      .get("players")
      .find((u) => u.get("id") === this.user.get("id"));

    const model = {
      ...this.model.toJSON(),
      forfeit: this.model.get("status") === "forfeit",
      chat: this.model.get("game_type") === "chat",
      war: this.model.get("game_type") === "war_time",
      friendly:
        this.model.get("game_type") === "chat" ||
        this.model.get("game_type") === "friendly",
      ladder: this.model.get("game_type") === "ladder",
      tournament: this.model.get("game_type") === "tournament",
      date: moment(this.model.get("created_at")).format("MM-DD-YYYY"),
      hour: moment(this.model.get("created_at")).format("LT"),
      opponent: opponent?.toJSON(),
      score:
        user && opponent
          ? `${user.get("points")}-${opponent.get("points")}`
          : "",
    };

    const template = $("#historyItemTemplate").html();
    const html = Mustache.render(template, model);
    this.$el.html(html);
    return this;
  }
}
