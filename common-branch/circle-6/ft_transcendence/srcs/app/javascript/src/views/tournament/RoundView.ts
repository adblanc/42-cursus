import Backbone from "backbone";
import Mustache from "mustache";
import Games from "src/collections/Games";
import BaseView from "src/lib/BaseView";
import MatchView from "./MatchView";

type Options = Backbone.ViewOptions & { collection: Games; round: string };

export default class RoundView extends BaseView {
  collection: Games;
  round: string;

  constructor(options?: Options) {
    super(options);

    this.collection = options.collection;
    this.round = options.round;
	this.listenTo(this.collection, "change", this.render);
  }

  render() {
    const template = $(`#round${this.round}Template`).html();
    const html = Mustache.render(template, {});
    this.$el.html(html);

    var nb = 1;
    this.collection.forEach(function (item) {
      var matchView = new MatchView({
        model: item,
        round: this.round,
        nb: nb,
      });
      this.$(`#round-${this.round}-game-${nb}`).append(matchView.render().el);
      nb++;
    }, this);

    return this;
  }
}
