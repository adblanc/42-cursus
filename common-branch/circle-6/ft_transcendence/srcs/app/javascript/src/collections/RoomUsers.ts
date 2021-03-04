import Backbone from "backbone";
import { currentUser } from "src/models/Profile";
import RoomUser from "src/models/RoomUser";

export default class RoomUsers extends Backbone.Collection<RoomUser> {
  initialize() {
    this.model = RoomUser;
  }

  currentRoomUser = () =>
    this.find((u) => u.get("id") === currentUser().get("id"));
}
