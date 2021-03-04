import Backbone from "backbone";
import RoomUsers from "src/collections/RoomUsers";
import BaseRoom from "./BaseRoom";
import RoomUser from "./RoomUser";

export default class PublicRoom extends BaseRoom {
  preinitialize() {
    this.relations = [
      {
        type: Backbone.Many,
        key: "users",
        collectionType: RoomUsers,
        relatedModel: RoomUser,
      },
    ];
  }
}
