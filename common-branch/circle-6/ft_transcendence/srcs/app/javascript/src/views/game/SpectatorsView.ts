import Mustache from "mustache";
import Spectators from "src/collections/Spectators";
import BaseView from "src/lib/BaseView";

interface Options {
  spectators: Spectators;
}

export default class SpectatorsView extends BaseView {
  spectators: Spectators;

  constructor({ spectators }: Options) {
    super();

    this.spectators = spectators;
    this.listenTo(this.spectators, "update", this.render);
  }

  render() {
    const template = $("#game-spectators-template").html();

    const html = Mustache.render(template, {
      spectators: this.spectators?.toJSON(),
      spectatorsNumber: this.spectators?.size(),
    });

    this.$el.html(html);

    return this;
  }
}
