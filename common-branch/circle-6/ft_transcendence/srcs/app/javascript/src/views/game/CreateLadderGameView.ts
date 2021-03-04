import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "../ModalView";
import SelectLadderView from "./SelectLadderView";
import { currentUser } from "src/models/Profile";
import RankedUsers from "src/collections/RankedUsers";
import { eventBus } from "src/events/EventBus";

export default class CreateLadderGameView extends ModalView {
  opponents: RankedUsers;

  constructor(options?: Backbone.ViewOptions) {
    super(options);

    this.opponents = new RankedUsers();
    this.opponents.fetch();

    this.listenTo(this.opponents, "update", this.render);
  }

  render() {
    super.render();
    const template = $("#ladderGameTemplate").html();
    const html = Mustache.render(template, currentUser().toJSON());
    this.$content.html(html);

    const $element = this.$("#listing");

    this.opponents.forEach(function (item) {
      if (item.get("ladder_rank") < currentUser().get("ladder_rank")) {
        var opponentView = new SelectLadderView({
          model: item,
        });
        $element.append(opponentView.render().el);
      }
    });

    return this;
  }
}
