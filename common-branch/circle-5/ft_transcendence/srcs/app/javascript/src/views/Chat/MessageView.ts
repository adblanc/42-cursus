import Backbone from "backbone";
import Mustache from "mustache";
import { eventBus } from "src/events/EventBus";
import Message from "src/models/Message";
import _ from "underscore";
import { formatMessageDate } from "src/utils";
import Game from "src/models/Game";

const MSG_TEMPLATE_ID = "#message-template";
const MSG_NOTIFICATION_TEMPLATE_ID = "#message-notification-template";

export default class MessageView extends Backbone.View<Message> {
  game: Game;

  constructor(options?: Backbone.ViewOptions<Message>) {
    super(options);

    if (!this.model) {
      throw Error("Please provide a Message model.");
    }

    if (this.model.get("game_id")) {
      this.game = new Game({ id: this.model.get("game_id") });
      this.game.fetch();

      this.listenTo(this.game, "change", this.render);
      this.listenTo(eventBus, "playchat:expired", this.fetchStatusUpdate);
    }
  }

  fetchStatusUpdate(game_id: number) {
    if (game_id == this.model.get("game_id")) {
      this.game.fetch({
        error: () => {
          this.game.set({ status: "finished" });
        },
      });
    }
  }

  events() {
    return {
      "click .user-avatar": () =>
        eventBus.trigger("chat:profile-clicked", this.model),
      "click #accept": "onAccept",
    };
  }

  async onAccept(e: JQuery.Event) {
    e.preventDefault();

    const success = await this.game.acceptPlayChat();
    if (success) {
      this.gameSaved();
    }
  }

  gameSaved() {
    this.game.navigateToGame();
  }

  render() {
    const isNotification = this.model.get("is_notification");

    const template = $(
      isNotification ? MSG_NOTIFICATION_TEMPLATE_ID : MSG_TEMPLATE_ID
    ).html();

    const { day, time } = formatMessageDate(this.model.get("created_at"));

    const html = Mustache.render(template, {
      ...this.model.toJSON(),
      day,
      time,
      req: !!this.game,
      pending: this.game?.get("status") === "pending",
    });

    this.$el.html(html);

    return this;
  }
}
