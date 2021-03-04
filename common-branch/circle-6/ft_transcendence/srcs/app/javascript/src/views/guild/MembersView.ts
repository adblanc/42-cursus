import Backbone from "backbone";
import Mustache from "mustache";
import Profiles from "src/collections/Profiles";
import MemberView from "./MemberView";
import PendingView from "./PendingView";
import Guild from "src/models/Guild";
import Profile, { currentUser } from "src/models/Profile";

type Options = Backbone.ViewOptions & { guild: Guild };

export default class MembersView extends Backbone.View {
  profiles: Profiles;
  guild: Guild;
  max: number;
  count: number;

  constructor(options?: Options) {
    super(options);

    this.guild = options.guild;
    this.profiles = this.guild.get("members");
    this.profiles.sort();
    this.max = 5;

    this.listenTo(this.guild, "change", this.render);
    this.listenTo(this.profiles, "update", this.render);
    this.listenTo(this.profiles, "sort", this.render);
    this.listenTo(currentUser(), "change", this.render);
  }

  events() {
    return {
      "click #pending-btn": this.onPendingClicked,
      "click #load-more": this.onLoadMore,
    };
  }

  onPendingClicked() {
    const pendingView = new PendingView({
      model: this.guild,
    });

    pendingView.render();
  }

  onLoadMore() {
    var members = this.profiles.models.slice(this.count, this.count + this.max);
    if (members.length) {
      members.forEach(function (item) {
        this.renderMember(item);
      }, this);
      this.count += members.length;
    }
    if (this.count == this.profiles.length) {
      this.$("#load-more").hide();
    }
  }

  render() {
    const template = $("#membersTemplate").html();
    const html = Mustache.render(template, this.guild.toJSON());
    this.$el.html(html);

    if (currentUser().get("guild")) {
      if (
        currentUser().get("guild").get("id") === this.guild.get("id") &&
        (currentUser().get("guild_role") === "Owner" ||
          currentUser().get("guild_role") === "Officer")
      ) {
        this.$("#pending").show();
      }
    }

    if (this.guild.get("pending_members")) {
      if (this.guild.get("pending_members").length > 0) {
        this.$("#pending-btn").addClass("animate-bounce");
      }
    }

    var members = this.profiles.first(this.max);
    members.forEach((item) => {
      this.renderMember(item);
    });
    this.count = members.length;
    if (this.count == this.profiles.length) {
      this.$("#load-more").hide();
    }

    return this;
  }

  renderMember(member: Profile) {
    var memberView = new MemberView({
      model: member,
      guild: this.guild,
    });
    this.$("#listing").append(memberView.render().el);
  }
}
