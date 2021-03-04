import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "src/lib/BaseView";
import Room from "src/models/Room";
import RoomMessagesView from "./RoomMessagesView";
import { eventBus } from "src/events/EventBus";

export default class MyRoomView extends BaseView<Room> {
  roomMessagesView: RoomMessagesView;

  constructor(options?: Backbone.ViewOptions<Room>) {
    super(options);

    if (!this.model) {
      throw Error("Please provide a Room model.");
    }

    this.listenTo(this.model, "change", this.render);
    this.listenTo(eventBus, "message:received", this.renderMessageReceived);

    this.roomMessagesView = undefined;
  }

  onClose = () => {
    this.roomMessagesView?.close();
    this.model.unsubscribe();
  };

  events() {
    return {
      "click .room-name": this.onClick,
    };
  }

  onClick() {
    if (!this.model.get("selected")) {
      this.model.select();
    }
    this.$("#message-pending").hide();
  }

  renderMessages() {
    if (this.roomMessagesView) {
      this.roomMessagesView.close();
    }
    this.roomMessagesView = new RoomMessagesView({ model: this.model });
    this.roomMessagesView.render();
  }

  renderMessageReceived(id) {
    if (id == this.model.get("id")) {
      this.$("#message-pending").show();
    }
  }

  render() {
    const template = $("#roomTemplate").html();
    const html = Mustache.render(template, this.model.toJSON());
    this.$el.html(html);

    if (this.model.get("selected")) {
      this.renderMessages();
    }

    return this;
  }
}
