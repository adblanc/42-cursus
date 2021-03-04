import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import Profile from "src/models/Profile";
import Guild from "src/models/Guild";
import { closeAllModal, displaySuccess } from "src/utils";

type Options = Backbone.ViewOptions & { model: Profile; guild: Guild };

export default class PendingMemberView extends BaseView {
  model: Profile;
  guild: Guild;

  constructor(options?: Options) {
    super(options);

    this.model = options.model;
    this.guild = options.guild;
  }

  events() {
    return {
      "click #accept-btn": "onAcceptClicked",
      "click #refuse-btn": "onRefuseClicked",
    };
  }

  async onAcceptClicked() {
    const success = await this.guild.accept(this.model.get("id"));

    if (success) {
      this.saved("accepted");
    }
  }

  async onRefuseClicked() {
    const success = await this.guild.reject(this.model.get("id"));

    if (success) {
      this.saved("refused");
    }
  }

  saved(method: "accepted" | "refused") {
    displaySuccess(`You ${method} ${this.model.get("name")} into your guild`);
    if (this.guild.get("pending_members").isEmpty()) {
      closeAllModal();
    }
  }

  render() {
    const template = $("#pendingMemberTemplate").html();
    const html = Mustache.render(template, this.model.toJSON());
    this.$el.html(html);

    return this;
  }
}
