import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import Profile, { currentUser } from "src/models/Profile";
import Guild from "src/models/Guild";
import ManageMemberView from "./ManageMemberView";

type Options = Backbone.ViewOptions & { model: Profile; guild: Guild };

export default class MemberView extends BaseView {
  model: Profile;
  guild: Guild;

  constructor(options?: Options) {
    super(options);

    this.model = options.model;
    this.guild = options.guild;

    this.listenTo(this.model, "change", this.render);
    this.listenTo(this.guild, "change", this.render);
    this.listenTo(this.guild.get("members"), "update", this.render);
    this.listenTo(currentUser(), "change", this.render);
  }

  events() {
    return {
      "click #manage-btn": "onManageClicked",
    };
  }

  onManageClicked() {
    const manageMemberView = new ManageMemberView({
      model: this.model,
      guild: this.guild,
    });

    manageMemberView.render();
  }

  render() {
    const template = $("#memberTemplate").html();

    const canBeManaged =
      (currentUser().get("guild") &&
        currentUser().get("guild").get("id") === this.guild.get("id") &&
        currentUser().get("guild_role") === "Owner" &&
        currentUser().get("id") != this.model.get("id")) ||
      (currentUser().get("admin") && this.model.get("guild_role") != "Owner");

    const html = Mustache.render(template, {
      ...this.model.toJSON(),
      pointsPercentage:
        (this.model.get("contribution") / this.guild.maxMemberPoints) * 100,
      canBeManaged,
    });
    this.$el.html(html);

    return this;
  }
}
