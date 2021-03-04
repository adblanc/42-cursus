import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import War from "src/models/War";
import Guild from "src/models/Guild";
import WarPendingView from "./WarPendingView";
import WarConfirmedView from "./WarConfirmedView";
import NoWarView from "./NoWarView";
import WarWaitingView from "./WarWaitingView";
import { eventBus } from "src/events/EventBus";
import { currentUser } from "src/models/Profile";

type Options = Backbone.ViewOptions & { guild: Guild };

export default class MyWarView extends BaseView {
  war: War;
  warPendingView: WarPendingView;
  warConfirmedView: WarConfirmedView;
  warWaitingView: WarWaitingView;
  noWarView: NoWarView;

  constructor(options?: Options) {
    super(options);

    this.warPendingView = undefined;
    this.warConfirmedView = undefined;
    this.warWaitingView = undefined;
    this.noWarView = undefined;
	this.guild?.fetch();

    this.listenTo(eventBus, "wars:update", this.onUpdate);
    this.listenTo(currentUser(), "change", this.onUpdate);
	this.listenTo(this.guild, "change", this.render);
  }

  onUpdate() {
    this.guild?.fetch({ success: () => this.render() });
  }

  setundefined(view: string) {
    if (view == "none") {
      this.warPendingView = undefined;
      this.warConfirmedView = undefined;
      this.warWaitingView = undefined;
    } else if (view == "pending") {
      this.warConfirmedView = undefined;
      this.warWaitingView = undefined;
      this.noWarView = undefined;
    } else if (view == "waiting") {
      this.warPendingView = undefined;
      this.warConfirmedView = undefined;
      this.noWarView = undefined;
    } else {
      this.warPendingView = undefined;
      this.warWaitingView = undefined;
      this.noWarView = undefined;
    }
  }

  private get guild() {
    return currentUser().get("guild");
  }

  chooseView() {
    if (!this.guild.get("atWar") && !this.guild.get("pendingWar")) {
      this.noWarView = new NoWarView();
      this.setundefined("none");
    } else if (this.guild.get("atWar")) {
      this.warConfirmedView = new WarConfirmedView({
        war: this.guild.get("activeWar"),
        guild: this.guild,
      });
      this.setundefined("confirmed");
    } else if (this.guild.get("pendingWar")) {
      if (this.guild.get("warInitiator")) {
        this.warWaitingView = new WarWaitingView({
          war: this.guild.get("waitingWar"),
          guild: this.guild,
        });
        this.setundefined("waiting");
      } else {
        this.warPendingView = new WarPendingView({
          collection: this.guild.get("pendingWars"),
          guild: this.guild,
        });
        this.setundefined("pending");
      }
    }
  }

  render() {
    if (!currentUser().get("guild")) {
      return this;
    }

    const template = $("#myWarTemplate").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);

    this.chooseView();

    if (this.warPendingView) {
      this.renderNested(this.warPendingView, "#content");
    } else if (this.warConfirmedView) {
      this.renderNested(this.warConfirmedView, "#content");
    } else if (this.warWaitingView) {
      this.renderNested(this.warWaitingView, "#content");
    } else if (this.noWarView) {
      this.renderNested(this.noWarView, "#content");
    }

    return this;
  }
}
