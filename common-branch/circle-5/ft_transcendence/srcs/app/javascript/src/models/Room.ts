import Backbone from "backbone";
import consumer from "channels/consumer";
import Messages from "src/collections/Messages";
import RoomUsers from "src/collections/RoomUsers";
import { BASE_ROOT } from "src/constants";
import { eventBus } from "src/events/EventBus";
import BaseRoom from "./BaseRoom";
import Message, { IMessage } from "./Message";
import { currentUser } from "./Profile";
import RoomUser from "./RoomUser";

export interface RoomData {
  event: "playchat:expired";
  game_id?: number;

  message: IMessage;
}

export default class Room extends BaseRoom {
  channel: ActionCable.Channel;
  messages: Messages;

  preinitialize() {
    this.relations = [
      {
        type: Backbone.Many,
        key: "users",
        collectionType: RoomUsers,
        relatedModel: RoomUser,
      },
      {
        type: Backbone.Many,
        key: "messages",
        collectionType: Messages,
        relatedModel: Message,
      },
    ];
  }

  initialize() {
    this.messages = new Messages();
    this.channel = this.createConsumer();

    this.listenTo(this, "change:id", this.updateChannel);
    this.listenTo(eventBus, "global:logout", this.onLogout);
  }

  urlRoot = () => `${BASE_ROOT}/rooms`;

  onLogout() {
    this.channel?.unsubscribe();
  }

  createConsumer() {
    const room_id = this.get("id");

    if (room_id === undefined) {
      return undefined;
    }

    this.unsubscribe();

    return consumer.subscriptions.create(
      { channel: "RoomChannel", room_id },
      {
        received: (data: RoomData) => {
          if (data.message) {
            const blocked = currentUser()
              .get("blocked_users")
              .find((u) => u.id === data.message.user_id);

            if (
              !data.message.ancient &&
              data.message.is_notification &&
              data.message.content.includes(
                `${currentUser().get("name")} has been banned`
              )
            ) {
              return this.quit();
            }

            if (!data.message.ancient && data.message.is_notification) {
              this.fetch();
            }

            if (!blocked) {
              this.messages.add(
                new Message({
                  ...data.message,
                  sent: currentUser().get("id") === data.message.user_id,
                })
              );
              if (
                !data.message.ancient &&
                currentUser().get("id") != data.message.user_id
              ) {
                eventBus.trigger("message:received", this.get("id"));
              }
            }
          }
          if (data.event === "playchat:expired") {
            eventBus.trigger(data.event, data.game_id);
          }
        },
      }
    );
  }

  updateChannel() {
    this.unsubscribe();
    this.channel = this.createConsumer();
  }

  unsubscribe() {
    this.channel?.unsubscribe();
  }

  select() {
    //@ts-ignore
    this.collection.setSelected(this);
  }

  toggle() {
    this.set("selected", !this.get("selected"));
  }

  async quit() {
    const success = await this.asyncDestroy({
      url: `${BASE_ROOT}/quit-room?id=${this.get("id")}`,
      wait: true,
    });

    if (success) {
      this.channel.unsubscribe();
    }

    return success;
  }

  async delete() {
    const success = await this.asyncDestroy({ wait: true });

    if (success) {
      this.unsubscribe();
    }
    return success;
  }

  modifyPassword(password: string) {
    return this.asyncSave({
      password,
    });
  }

  createDm(id: number) {
    return this.asyncSave(
      {},
      {
        url: `${BASE_ROOT}/direct_messages/${id}`,
      }
    );
  }
}
