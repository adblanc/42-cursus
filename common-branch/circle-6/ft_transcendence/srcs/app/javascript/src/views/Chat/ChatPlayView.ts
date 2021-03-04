import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "../ModalView";
import Message from "src/models/Message";
import Game from "src/models/Game";
import { currentUser } from "src/models/Profile";

type Options = Backbone.ViewOptions<Game> & {
  room_id: number;
};

export default class ChatPlayView extends ModalView<Game> {
  room_id: number;
  level: string;
  goal: number;

  constructor(options?: Options) {
    super(options);

    this.room_id = options.room_id;
  }

  events() {
    return { ...super.events(), "click #input-chatplay-submit": "onSubmit" };
  }

  async onSubmit(e: JQuery.Event) {
    e.preventDefault();

    this.level = this.$("#level").val() as string;
    this.goal = this.$("#goal").val() as number;

    const success = await this.model.playChat(
      this.level,
      this.goal,
      this.room_id
    );
    if (success) {
      const msgSuccess = await this.gameSaved();

      if (msgSuccess) {
        currentUser().set({ pendingGame: this.model });
      }
    }
  }

  gameSaved() {
    this.closeModal();
    this.model.createChannelConsumer();
    const content = `Let's play a game! Difficulty : ${this.level}. Points : ${this.goal}`;
    const message = new Message({
      content,
      room_id: this.room_id,
      game_id: this.model.get("id"),
    });
    return message.asyncSave();
  }

  render() {
    super.render();
    const template = $("#chatplayTemplate").html();
    const html = Mustache.render(template, {});
    this.$content.html(html);

    return this;
  }
}
