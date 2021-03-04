import { BASE_ROOT } from "src/constants";
import { eventBus } from "src/events/EventBus";
import PublicRoom from "src/models/PublicRoom";
import Room from "../models/Room";
import BaseRooms from "./BaseRooms";

export default class MyRooms extends BaseRooms<Room> {
  selectedRoom?: Room;
  preinitialize() {
    this.model = Room;
  }

  constructor() {
    super();

    this.selectedRoom = undefined;
    this.listenTo(this, "remove", this.onRemove);
    this.listenTo(eventBus, "chat:public-channel-joined", this.addPublicRoom);
    this.listenTo(eventBus, "chat:other-user-dm-creation", this.fetch);
    this.listenTo(eventBus, "chat:rooms_global:created", this.fetch);
    this.listenTo(eventBus, "chat:my-room-left", this.fetch);
  }

  addPublicRoom(publicRoom: PublicRoom) {
    const roomInAdminList = this.find(
      (r) => r.get("isInAdminList") && r.get("id") === publicRoom.get("id")
    );

    if (roomInAdminList) {
      roomInAdminList.unsubscribe();
      this.remove(roomInAdminList);
    }

    const room = new Room({ ...publicRoom.toJSON(), isInAdminList: false });

    this.add(room);
  }

  onRemove(room: Room) {
    room.unsubscribe();
    this.checkSelectedRemove(room);
  }

  checkSelectedRemove(room: Room) {
    if (room === this.selectedRoom) {
      if (this.size()) {
        this.setSelected(this.first());
      } else {
        this.selectedRoom = undefined;
      }
    }
  }

  setSelected(room: Room) {
    if (
      this.selectedRoom &&
      this.find((r) => r.get("id") === this.selectedRoom?.get("id"))
    ) {
      this.selectedRoom?.toggle();
    }
    this.selectedRoom = room;
    this.selectedRoom?.toggle();
    eventBus.trigger("chat:room-selected");
  }

  url = () => `${BASE_ROOT}/my-rooms`;
}
