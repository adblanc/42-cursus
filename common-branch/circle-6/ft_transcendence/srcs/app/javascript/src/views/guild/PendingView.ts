import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "../ModalView";
import Profiles from "src/collections/Profiles";
import Guild from "src/models/Guild";
import PendingMemberView from "./PendingMemberView";
import Profile from "src/models/Profile";

export default class PendingView extends ModalView<Guild> {
  profiles: Profiles;

  constructor(options?: Backbone.ViewOptions<Guild>) {
    super(options);

    this.profiles = this.model.get("pending_members");

    this.listenTo(this.profiles, "remove", this.onRemove);
  }

  onRemove(profile: Profile) {
    this.$(`#pending-member-${profile.get("id")}`)
      .parent()
      .remove();

    if (this.profiles.isEmpty()) {
      this.renderIsEmpty();
    }
  }

  renderIsEmpty() {
    if (this.profiles.isEmpty()) {
      this.$("#notEmpty").hide();
      this.$("#empty").show();
    } else {
      this.$("#empty").hide();
      this.$("#notEmpty").show();
    }
  }

  render() {
    super.render();
    const template = $("#pendingTemplate").html();
    const html = Mustache.render(template, this.model.toJSON());
    this.$content.html(html);
    this.renderIsEmpty();

    this.profiles.forEach((item) => {
      this.$("#listing").append(
        new PendingMemberView({
          model: item,
          guild: this.model,
        }).render().el
      );
    }, this);

    return this;
  }
}
