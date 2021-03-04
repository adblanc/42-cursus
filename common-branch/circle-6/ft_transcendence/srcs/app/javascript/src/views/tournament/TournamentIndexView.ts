import Mustache from "mustache";
import Backbone from "backbone";
import BaseView from "src/lib/BaseView";
import { eventBus } from "src/events/EventBus";

export default class TournamentIndexView extends BaseView {
  constructor(options?: Backbone.ViewOptions) {
    super(options);
  }

  render() {
    const template = $("#tournamentTemplate").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);

    return this;
  }
}
