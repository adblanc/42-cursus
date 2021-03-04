import BaseView from "src/lib/BaseView";
import Room from "src/models/Room";
import RoomUser from "src/models/RoomUser";
import RoomUserView from "./RoomUserView";

const sortByRole = (user: RoomUser) => {
  switch (user.get("roomRole")) {
    case "Owner":
      return 0;
    case "Administrator":
      return 1;
    default:
      return 2;
  }
};

export default class RoomUsersView extends BaseView<Room> {
  currentRoomUser?: RoomUser;

  constructor(options?: Backbone.ViewOptions<Room>) {
    super(options);

    if (!this.model) {
      throw Error("Please provide Room model to this view.");
    }

    this.currentRoomUser = this.model.get("users").currentRoomUser();

    this.listenTo(this.model, "change", this.render);
  }

  renderRoomUser(roomUser: RoomUser) {
    this.$el.append(
      new RoomUserView({
        model: roomUser,
        currentRoomUser: this.currentRoomUser,
      }).render().el
    );
  }

  render() {
    this.$el.html("");
    this.model
      .get("users")
      .sortBy(sortByRole)
      .forEach((user) => this.renderRoomUser(user));

    return this;
  }
}
