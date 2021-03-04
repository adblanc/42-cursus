import Mustache from "mustache";
import BaseView from "src/lib/BaseView";
import Game from "src/models/Game";

export default class GameToSpectateView extends BaseView<Game> {
  constructor(options: Backbone.ViewOptions<Game>) {
    super(options);

    this.verifyModelExists();

    this.listenTo(this.model.get("spectators"), "update", this.render);
  }

  render() {
    const template = $("#game-to-spectate-template").html();

    const html = Mustache.render(template, {
      ...this.model.toJSON(),
      spectatorsNbr: this.model.spectatorsNbr,
      firstPlayer: this.model.get("players").at(0)?.toJSON(),
      secondPlayer: this.model.get("players").at(1)?.toJSON(),
      link: `/game/${this.model.get("id")}`,
    });

    this.$el.html(html);

    return this;
  }
}
