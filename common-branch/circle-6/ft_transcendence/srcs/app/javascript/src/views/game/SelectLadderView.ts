import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import { currentUser } from "src/models/Profile";
import { displaySuccess } from "src/utils/toast";
import Game from "src/models/Game";
import User from "src/models/User";
import { closeAllModal } from "src/utils";

type Options = Backbone.ViewOptions & { model: User };

export default class SelectLadderView extends BaseView {
  model: User;
  game: Game;

  constructor(options?: Options) {
    super(options);

    this.model = options.model;
  }

  events() {
    return {
      "click #challenge-ladder": "onChallenge",
    };
  }

  async onChallenge(e: JQuery.Event) {
    e.preventDefault();
    this.game = new Game();
    const success = await this.game.ladderChallenge(this.model.get("id"));
    if (success) {
      this.gameSaved();
    }
  }

  gameSaved() {
    closeAllModal();
    displaySuccess(`Waiting for ${this.model.get("name")}`);
    currentUser().fetch();
    this.game.createChannelConsumer();
  }

  render() {
    const template = $("#selectLadderTemplate").html();
    const html = Mustache.render(template, {
      ...this.model.toJSON(),
      challengeable: this.model.isLadderChallengeable(),
      justlost: this.model.justLostLadder(),
    });
    this.$el.html(html);

    return this;
  }
}
