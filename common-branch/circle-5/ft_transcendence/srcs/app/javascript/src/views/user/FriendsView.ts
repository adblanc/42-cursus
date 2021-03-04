import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "../ModalView";
import Friends from "src/collections/Friends";
import User from "src/models/User";
import ItemFriendView from "./ItemFriendView";
import { eventBus } from "src/events/EventBus";

export default class FriendsView extends ModalView<User> {
  friends: Friends;

  constructor(options?: Backbone.ViewOptions<User>) {
    super(options);

    this.friends = this.model.get("friends");

    this.listenTo(this.friends, "remove", this.onRemove);
  }

  onRemove(friend: User) {
    this.$(`#friend-${friend.get("id")}`)
      .parent()
      .remove();

    if (this.friends.isEmpty()) {
      this.renderIsEmpty();
    }
    eventBus.trigger("user:change");
  }

  renderIsEmpty() {
    if (this.friends.isEmpty()) {
      this.$("#notEmpty").hide();
      this.$("#empty").show();
    } else {
      this.$("#empty").hide();
      this.$("#notEmpty").show();
    }
  }

  render() {
    super.render();
    const template = $("#friendsTemplate").html();
    const html = Mustache.render(template, {});
    this.$content.html(html);
    this.renderIsEmpty();

    this.friends.forEach((item) => {
      this.$("#listing").append(
        new ItemFriendView({
          model: item,
          user: this.model,
        }).render().el
      );
    }, this);

    return this;
  }
}
