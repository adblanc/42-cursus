import Backbone from "backbone";
import { eventBus } from "src/events/EventBus";
import BaseView from "src/lib/BaseView";
import Message from "src/models/Message";
import Room from "src/models/Room";
import RoomUser from "src/models/RoomUser";
import MessageView from "./MessageView";
import RoomUserProfileView from "./RoomUserProfileView";

export default class RoomMessagesView extends BaseView<Room> {
  constructor(options?: Backbone.ViewOptions<Room>) {
    super(options);

    if (!this.model) {
      throw Error("Please provide a Room model.");
    }

    this.listenTo(this.model.messages, "add", this.renderMsg);

    this.listenTo(eventBus, "chat:profile-clicked", this.showProfileModal);
  }

  showProfileModal(message: Message) {
    if (message.get("room_id") !== this.model.get("id")) {
      return;
    }

    const sender =
      this.model
        .get("users")
        .find((u) => u.get("id") === message.get("user_id")) ||
      new RoomUser({
        id: message.get("user_id"),
        name: message.get("pseudo"),
        login: "",
        roomRole: "Former member",
        avatar_url: message.get("avatar_url"),
      });

    const profileView = new RoomUserProfileView({
      model: sender,
      currentRoomUser: this.model.get("users").currentRoomUser(),
    });

    profileView.render();
  }

  renderMsg(message: Message) {
    if (!this.model.get("selected")) {
      return;
    }

    const container = $("#messages-container");

    const isScrolledToBottom =
      container.prop("scrollHeight") - container.prop("clientHeight") <=
      container.prop("scrollTop") + 1;

    container.append(new MessageView({ model: message }).render().el);

    if (isScrolledToBottom) {
      this.scrollToBottom();
    }
  }

  scrollToBottom() {
    $("#messages-container").scrollTop(
      $("#messages-container").prop("scrollHeight")
    );
  }

  render() {
    $("#messages-container").children().remove();
    this.model.messages.forEach((msg) => this.renderMsg(msg));

    return this;
  }
}
