import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "../ModalView";
import FriendRequests from "src/collections/FriendRequests";
import User from "src/models/User";
import ItemRequestView from "./ItemRequestView"
import { eventBus } from "src/events/EventBus";

export default class RequestsView extends ModalView<User> {
  requests: FriendRequests;

  constructor(options?: Backbone.ViewOptions<User>) {
    super(options);

	this.requests = this.model.get("friend_requests");

    this.listenTo(this.requests, "remove", this.onRemove);
  }

  onRemove(request: User) {
    this.$(`#pending-request-${request.get("id")}`)
      .parent()
      .remove();

    if (this.requests.isEmpty()) {
      this.renderIsEmpty();
	}
	eventBus.trigger("user:change");
  }

  renderIsEmpty() {
    if (this.requests.isEmpty()) {
      this.$("#notEmpty").hide();
      this.$("#empty").show();
    } else {
      this.$("#empty").hide();
      this.$("#notEmpty").show();
    }
  }

  render() {
    super.render();
    const template = $("#requestsTemplate").html();
    const html = Mustache.render(template, {});
    this.$content.html(html);
    this.renderIsEmpty();

    this.requests.forEach((item) => {
      this.$("#listing").append(
        new ItemRequestView({
		  model: item,
		  user: this.model,
        }).render().el
      );
    }, this);

    return this;
  }
}
