import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import User from "src/models/User";
import { displaySuccess } from "src/utils";

type Options = Backbone.ViewOptions & { model: User; user: User };

export default class ItemFriendView extends BaseView {
  model: User;
  user: User;

  constructor(options?: Options) {
    super(options);

    this.model = options.model;
    this.user = options.user;

    this.listenTo(this.model, "change", this.render);
  }

  events() {
    return {
      "click #remove-btn": this.onRemoveFriend,
    };
  }

  async onRemoveFriend() {
    const success = await this.model.removeFriend();

    if (success) {
      displaySuccess(
        `Your are no longer friend with ${this.model.get("name")}`
      );
    }
    this.user.fetch();
  }

  render() {
    const template = $("#friendItemTemplate").html();
    const html = Mustache.render(template, this.model.toJSON());
    this.$el.html(html);

    return this;
  }
}
