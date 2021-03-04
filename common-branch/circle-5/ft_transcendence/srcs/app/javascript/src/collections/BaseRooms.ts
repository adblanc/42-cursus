import Backbone from "backbone";
import { RoomsGlobalData } from "channels/rooms_global_channel";
import { eventBus } from "src/events/EventBus";
import BaseRoom from "src/models/BaseRoom";

export default class BaseRooms<
  T extends BaseRoom
> extends Backbone.Collection<T> {
  constructor() {
    super();
    this.listenTo(
      eventBus,
      "chat:rooms_global:deleted",
      this.onGlobalRoomDelete
    );
  }

  onGlobalRoomDelete(data: RoomsGlobalData) {
    const room = this.find((r) => r.get("id") === data.payload.id);

    if (room) {
      this.remove(room);
    }
  }
}
