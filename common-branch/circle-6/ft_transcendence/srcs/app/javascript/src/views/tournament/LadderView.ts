import Mustache from "mustache";
import Backbone from "backbone";
import BaseView from "src/lib/BaseView";
import LadderOpponentView from "./LadderOpponentView";
import { currentUser } from "src/models/Profile";
import RankedUsers from "src/collections/RankedUsers";
import { displaySuccess } from "src/utils/toast";
import User from "src/models/User";

export default class LadderView extends BaseView {
  opponents: RankedUsers;
  max: number;
  count: number;

  constructor(options?: Backbone.ViewOptions) {
    super(options);

    this.opponents = new RankedUsers();
    this.opponents.fetch();
    this.opponents.sort();
    this.max = 5;

    this.listenTo(this.opponents, "update", this.render);
    this.listenTo(this.opponents, "sort", this.render);
    this.listenTo(currentUser(), "change", this.update);
  }

  update() {
    this.opponents.fetch();
    this.opponents.sort();
  }

  events() {
    return {
      "click #load-more": this.onLoadMore,
      "click #accept-btn": this.onAccept,
    };
  }

  async onAccept(e: JQuery.Event) {
    e.preventDefault();
    const success = await currentUser()
      .get("pendingGameToAccept")
      .acceptLadderChallenge();
    if (success) {
      this.gameSaved();
    }
  }

  gameSaved() {
    displaySuccess(`Ladder Game accepted!`);
    currentUser().fetch();
    currentUser().get("pendingGameToAccept").navigateToGame();
  }

  renderOpponent(opponent: User) {
    var opponentView = new LadderOpponentView({
      model: opponent,
    });
    this.$("#list").append(opponentView.render().el);
  }

  onLoadMore() {
    var opponents = this.opponents.models.slice(
      this.count,
      this.count + this.max
    );
    if (opponents.length) {
      opponents.forEach(function (item) {
        this.renderOpponent(item);
      }, this);
      this.count += opponents.length;
    }
    if (this.count == this.opponents.length) {
      this.$("#load-more").hide();
    }
  }

  render() {
    const template = $("#ladderTemplate").html();
    const html = Mustache.render(template, currentUser().toJSON());
    this.$el.html(html);

    var opponents = this.opponents.first(this.max);
    opponents.forEach((item) => {
      this.renderOpponent(item);
    });
    this.count = opponents.length;
    if (this.count == this.opponents.length) {
      this.$("#load-more").hide();
    }

    if (currentUser().get("pendingGame")) {
      if (currentUser().get("pendingGame").get("game_type") == "ladder")
        this.$("#waiting").show();
      else this.$("#unavailable-pend").show();
    } else if (
      currentUser().get("matchedGame") ||
      currentUser().get("currentGame")
    )
      this.$("#unavailable-start").show();
    else if (currentUser().get("pendingGameToAccept")) {
      this.$("#accept").show();
    } else {
      this.$("#default").show();
    }

    return this;
  }
}
