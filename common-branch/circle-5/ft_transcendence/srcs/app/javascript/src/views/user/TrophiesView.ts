import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "src/lib/BaseView";
import TrophyView from "./TrophyView";
import Tournaments from "src/collections/Tournaments";

type Options = Backbone.ViewOptions & { tournaments: Tournaments };

export default class TrophiesView extends BaseView {
  tournaments: Tournaments;

  constructor(options: Options) {
    super(options);

    this.tournaments = options.tournaments;
  }

  render() {
    const template = $("#trophiesTemplate").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);
    const $element = this.$("#listing");

    this.tournaments.forEach(function (item) {
      var trophyView = new TrophyView({
        model: item,
      });
      $element.append(trophyView.render().el);
    });

    return this;
  }
}
