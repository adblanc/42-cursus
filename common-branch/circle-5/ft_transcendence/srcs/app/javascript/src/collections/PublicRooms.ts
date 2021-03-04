import { BASE_ROOT } from "src/constants";
import { eventBus } from "src/events/EventBus";
import PublicRoom from "src/models/PublicRoom";
import BaseRooms from "./BaseRooms";

export default class PublicRooms extends BaseRooms<PublicRoom> {
  preinitialize() {
    this.model = PublicRoom;

    this.listenTo(eventBus, "chat:my-room-left", this.fetch);
    this.listenTo(eventBus, "chat:rooms_global:created", this.fetch);
  }

  url = () => `${BASE_ROOT}/rooms`;
}
