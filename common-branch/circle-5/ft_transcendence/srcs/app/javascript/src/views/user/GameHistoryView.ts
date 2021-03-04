import Backbone from "backbone";
import Mustache from "mustache";
import User from "src/models/User";
import BaseView from "src/lib/BaseView";
import HistoryItemView from "./HistoryItemView";
import Games from "src/collections/Games";

type Options = Backbone.ViewOptions & { user: User };

export default class GameHistoryView extends BaseView {
  user: User;
  games: Games;
  count: number = 0;
  max: number = 5;

  constructor(options: Options) {
    super(options);

    this.user = options.user;
    this.games = this.user.get("games");
  }

  events() {
    return {
      "click #load-more-game": this.loadMoreGame,
    };
  }

  loadMoreGame() {
    var games = this.games.models.slice(this.count, this.count + this.max);
    if (games.length) {
      games.forEach((item) => {
        var historyItemView = new HistoryItemView({
          model: item,
          user: this.user,
        });
        const $element = this.$("#listing_game");
        $element.append(historyItemView.render().el);
        this.count += 1;
      });
    }
    if (this.count == this.games.length) {
      this.$("#load-more-game").hide();
    }
  }

  render() {
    const template = $("#gameHistoryTemplate").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);
    const $element = this.$("#listing_game");

    if (this.games == undefined || this.games.length == 0) {
      this.$("#no-history").show();
      this.$("#load-more-game").hide();
    } else {
      var games = this.games.first(this.max);
      games.forEach((item) => {
        var historyItemView = new HistoryItemView({
          model: item,
          user: this.user,
        });
        $element.append(historyItemView.render().el);
      });

      this.count += games.length;
      if (this.count == this.games.length) {
        this.$("#load-more-game").hide();
      }
    }

    return this;
  }
}
