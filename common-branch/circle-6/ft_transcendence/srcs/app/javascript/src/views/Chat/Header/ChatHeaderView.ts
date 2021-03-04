import Backbone from "backbone";
import Mustache from "mustache";
import Rooms from "src/collections/MyRooms";
import { eventBus } from "src/events/EventBus";
import BaseView from "src/lib/BaseView";
import { displayError, displaySuccess } from "src/utils";
import ConfirmationModalView from "src/views/ConfirmationModalView";
import _ from "underscore";
import ManageRoomView from "./ManageRoomView";

type Options = Backbone.ViewOptions & {
  rooms: Rooms;
};

export default class ChatHeaderView extends BaseView {
  rooms: Rooms;

  constructor(options?: Options) {
    super(options);

    if (!options.rooms) {
      throw Error("Please provide a room collection to this view.");
    }

    this.rooms = options.rooms;

    this.listenTo(this.rooms, "change", this.render);
  }

  events() {
    return {
      "click #manage-room": this.manageRoom,
      "click #quit-room": this.askConfirmationQuit,
    };
  }

  askConfirmationQuit() {
    const { selectedRoom } = this.rooms;

    const question = selectedRoom?.get("is_dm")
      ? `Are you sure you want to delete your messages with ${selectedRoom?.get(
          "name"
        )} ?`
      : `Are you sure you want to quit ${selectedRoom?.get("name")} ?`;

    const confirmationView = new ConfirmationModalView({
      question,
      onYes: this.quitRoom,
    });

    confirmationView.render();
  }

  quitRoom = async () => {
    const { selectedRoom } = this.rooms;

    const success = await selectedRoom?.quit();

    if (success) {
      const action = success.get("is_dm")
        ? "destroyed"
        : success.get("users").length - 1 > 0
        ? "left"
        : "destroyed";

      if (action === "left") {
        eventBus.trigger("chat:my-room-left");
      }

      const msg = selectedRoom?.get("is_dm")
        ? `Messages with ${selectedRoom?.get("name")} successfully ${action}`
        : `Room ${selectedRoom?.get("name")} successfully ${action}`;
      displaySuccess(msg);
    }
  };

  async manageRoom() {
    if (this.rooms.selectedRoom) {
      new ManageRoomView({ model: this.rooms.selectedRoom }).render();
    } else {
      displayError("room not found");
    }
  }

  render() {
    const template = $("#chat-header-template").html();
    const html = Mustache.render(template, {
      ...this.rooms.selectedRoom?.toJSON(),
    });

    this.$el.html(html);

    return this;
  }
}
