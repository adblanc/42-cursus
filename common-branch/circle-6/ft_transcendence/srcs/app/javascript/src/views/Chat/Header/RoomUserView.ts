import Mustache from "mustache";
import BaseView from "src/lib/BaseView";
import RoomUser from "src/models/RoomUser";
import RoomUserProfileView from "../RoomUserProfileView";

type Options = Backbone.ViewOptions<RoomUser> & {
  currentRoomUser: RoomUser;
};

export default class RoomUserView extends BaseView<RoomUser> {
  currentRoomUser: RoomUser;

  constructor(options?: Options) {
    super(options);

    this.listenTo(this.model, "change", this.render);

    this.currentRoomUser = options.currentRoomUser;
  }

  events() {
    return {
      "click #manage-user": this.manageUser,
    };
  }

  manageUser() {
    const profileView = new RoomUserProfileView({
      model: this.model,
      currentRoomUser: this.currentRoomUser,
    });

    profileView.render();
  }

  render() {
    const template = $("#room-user-template").html();

    const html = Mustache.render(template, {
      ...this.model.toJSON(),
    });
    this.$el.html(html);

    return this;
  }
}
