import Backbone from "backbone";
import Mustache from "mustache";
import MyRooms from "src/collections/MyRooms";
import BaseView from "src/lib/BaseView";
import Room from "src/models/Room";
import MyRoomView from "./MyRoomView";

type Options = Backbone.ViewOptions & {
  myRooms: MyRooms;
};

const ADMIN_ROOMS_VIEW_INFOS = {
  label: "Admin channels list",
  id: "admin-rooms-list",
};

export default class AdminRoomsView extends BaseView {
  myRooms: MyRooms;
  adminRoomViews: MyRoomView[];

  constructor(options?: Options) {
    super(options);

    this.adminRoomViews = [];
    this.myRooms = options.myRooms;

    this.listenTo(this.myRooms, "add", this.renderAdminRoom);
    this.listenTo(this.myRooms, "remove", this.removeAdminRoom);
  }

  onClose = () => {
    this.myRooms.forEach((room) => this.removeAdminRoom(room));
  };

  renderAdminRoom(room: Room) {
    if (room.get("isInAdminList")) {
      const myRoomView = new MyRoomView({ model: room });
      this.adminRoomViews.push(myRoomView);
      this.$("#admin-rooms-list").append(myRoomView.render().el);
    }
  }

  removeAdminRoom(room: Room) {
    if (room.get("isInAdminList")) {
      this.adminRoomViews.forEach((r) => {
        if (r.model.get("id") === room.get("id")) {
          r.close();
        }
      });
    }
  }

  render() {
    const template = $("#rooms-list-template").html();
    const html = Mustache.render(template, ADMIN_ROOMS_VIEW_INFOS);
    this.$el.html(html);

    return this;
  }
}
