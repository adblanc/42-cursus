import Backbone from "backbone";
import Mustache from "mustache";
import Rooms from "src/collections/MyRooms";
import { eventBus } from "src/events/EventBus";
import BaseView from "src/lib/BaseView";
import Room from "src/models/Room";
import { displaySuccess } from "src/utils";

type Options = Backbone.ViewOptions & {
  rooms: Rooms;
};

export default class CreateJoinChannelView extends BaseView {
  isJoin: boolean;
  rooms: Rooms;
  isPrivate: boolean;

  constructor(options: Options) {
    super(options);

    if (!options.rooms) {
      throw Error("Please provide a room collection to this view.");
    }

    this.isJoin = false;
    this.isPrivate = false;
    this.rooms = options.rooms;
  }

  events() {
    return {
      "click #switch-create-join": this.switchCreateJoin,
      "click #create-channel": this.onSubmit,
      "click #switch-private": this.switchPrivate,
    };
  }

  private nameInput = () => this.$("#channel-name");
  private passwordInput = () => this.$("#channel-password");

  switchCreateJoin() {
    this.isJoin = !this.isJoin;
    if (this.isJoin) {
      this.isPrivate = true;
    }
    this.render();
  }

  async onSubmit() {
    const name = this.nameInput().val() as string;
    const password = this.passwordInput().val() as string;

    const { success, room } = !this.isJoin
      ? await this.createChannel(name, password)
      : await this.joinChannel(name, password);

    if (success) {
      eventBus.trigger("chat:public-channel-joined", room);
      this.clearInput();
      displaySuccess(
        `Room ${name} successfully ${this.isJoin ? "joined" : "created"}.`
      );
    }
  }

  async createChannel(name: string, password: string) {
    const room = new Room();
    const success = await room.asyncSave({
      name: name,
      password: password,
      is_private: this.isPrivate,
    });

    return { room, success };
  }

  async joinChannel(name: string, password: string) {
    const room = new Room({
      name,
      password,
      is_private: this.isPrivate,
    });

    const success = await room.join();

    return { room, success };
  }

  private clearInput() {
    this.nameInput().val("");
    this.passwordInput().val("");
  }

  switchPrivate() {
    this.isPrivate = !this.isPrivate;
    this.render();
  }

  render() {
    const template = $("#create-join-channel-template").html();
    const html = Mustache.render(template, {
      isJoin: this.isJoin,
      isPrivate: this.isPrivate,
    });
    this.$el.html(html);

    return this;
  }
}
