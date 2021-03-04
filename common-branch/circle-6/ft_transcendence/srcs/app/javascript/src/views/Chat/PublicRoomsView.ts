import Backbone from "backbone";
import Mustache from "mustache";
import PublicRooms from "src/collections/PublicRooms";
import BaseView from "src/lib/BaseView";
import PublicRoom from "src/models/PublicRoom";
import PublicRoomView from "./PublicRoomView";

type Options = Backbone.ViewOptions & {
  publicRooms: PublicRooms;
};

const PUBLIC_ROOMS_VIEW_INFOS = {
  label: "Public channels list",
  id: "public-rooms-list",
};

export default class PublicRoomsView extends BaseView {
  publicRooms: PublicRooms;

  constructor(options?: Options) {
    super(options);

    this.publicRooms = new PublicRooms();
    this.publicRooms.fetch();

    this.listenTo(this.publicRooms, "add", this.renderPublicRoom);
    this.listenTo(this.publicRooms, "remove", this.removePublicRoom);
  }

  renderPublicRoom(room: PublicRoom) {
    this.$("#public-rooms-list").append(
      new PublicRoomView({ model: room }).render().el
    );
  }

  removePublicRoom(room: PublicRoom) {
    this.$(`#room-${room.get("id")}`)
      .parent()
      .remove();
  }

  render() {
    const template = $("#rooms-list-template").html();
    const html = Mustache.render(template, PUBLIC_ROOMS_VIEW_INFOS);
    this.$el.html(html);

    return this;
  }
}
