import Backbone from "backbone";
import Mustache from "mustache";
import Rooms from "src/collections/MyRooms";
import BaseView from "src/lib/BaseView";
import Message from "src/models/Message";
import Game from "src/models/Game";
import ChatPlayView from "./ChatPlayView";
import _ from "underscore";
import { eventBus } from "src/events/EventBus";

type Options = Backbone.ViewOptions & {
  rooms: Rooms;
};

export default class ChatInputView extends BaseView {
  rooms: Rooms;

  constructor(options?: Options) {
    super(options);

    this.rooms = options.rooms;
    this.listenTo(eventBus, "chat:room-selected", this.render);
  }

  events() {
    return {
      "keypress #send-message-input": this.onKeyPress,
      "click #send-message-btn": this.sendMessage,
      "click #chat-play-btn": this.onPlay,
    };
  }

  onPlay() {
    const game = new Game();
    const chatPlayView = new ChatPlayView({
      model: game,
      room_id: this.rooms.selectedRoom?.get("id"),
    });

    chatPlayView.render();
  }

  async onKeyPress(e: JQuery.Event) {
    if (e.key !== "Enter") {
      return;
    }
    e.preventDefault();

    await this.sendMessage();
  }

  sendMessage() {
    const content = this.$("#send-message-input").val() as string;

    if (!content) {
      return;
    }

    const message = new Message({
      content,
      room_id: this.rooms.selectedRoom?.get("id"),
    });

    this.clearInput();

    return message.asyncSave();
  }

  clearInput() {
    this.$("#send-message-input").val("");
  }

  render() {
    const template = $("#chat-input-template").html();
    const html = Mustache.render(template, {
      dm: this.rooms.selectedRoom?.get("is_dm"),
    });
    this.$el.html(html);

    return this;
  }
}
