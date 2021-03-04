import Mustache from "mustache";
import Backbone from "backbone";
import BaseView from "src/lib/BaseView";
import Game from "src/models/Game";
import { currentUser } from "src/models/Profile";

export default class StartGameView extends BaseView<Game> {
  constructor(options?: Backbone.ViewOptions<Game>) {
    super(options);
  }

  events() {
    return {
      "click #cancel-friendly": this.onCancelFriendly,
    };
  }

  async onCancelFriendly() {
    await this.model.cancelFriendly();

    currentUser().set({ pendingGame: null });
  }

  render() {
    const template = $("#waitingOpponentTemplate").html();

    const isWar = this.model.get("game_type") === "war_time";
    const isLadder = this.model.get("game_type") === "ladder";
    const isTour = this.model.get("game_type") === "tournament";
    const isClassic = !isWar && !isLadder && !isTour;

    const html = Mustache.render(template, {
      time: this.model.get("war_time")?.get("time_to_answer"),
      isWar,
      isLadder,
      isClassic,
      isTour,
    });
    this.$el.html(html);

    return this;
  }
}
