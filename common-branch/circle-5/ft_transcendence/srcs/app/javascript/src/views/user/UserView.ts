import Backbone from "backbone";
import Mustache from "mustache";
import moment from "moment";
import User from "src/models/User";
import BaseView from "src/lib/BaseView";
import RequestsView from "./RequestsView";
import FriendsView from "./FriendsView";
import { eventBus } from "src/events/EventBus";
import { currentUser } from "src/models/Profile";
import { displaySuccess } from "src/utils";
import GameHistoryView from "./GameHistoryView";
import TrophiesView from "./TrophiesView";

type Options = Backbone.ViewOptions & { userId: number };

export default class UserView extends BaseView {
  user: User;

  constructor(options: Options) {
    super(options);

    this.user = new User({ id: options.userId, login: "" });
    this.user.fetch();
    this.listenTo(currentUser(), "change", this.render);
    this.listenTo(this.user, "change", this.render);
    this.listenTo(this.user.get("games"), "update", this.render);
    this.listenTo(this.user.get("won_tournaments"), "update", this.render);
    this.listenTo(eventBus, "user:change", this.render);
    this.listenTo(eventBus, "profile:change", this.actualize);
  }

  events() {
    return {
      "click #send-dm": this.onClickSendDm,
      "click #add-friend": this.onAddFriend,
      "click #remove-friend": this.onRemoveFriend,
      "click #request-btn": "onRequestClicked",
      "click #friends-btn": "onFriendsClicked",
      "click #ban-user": this.onUserBan,
      "click #unban-user": this.onUserUnban,
      "click #admin-user": this.onUserAdmin,
      "click #unadmin-user": this.onUserUnAdmin,
    };
  }

  async onUserAdmin() {
    const success = await currentUser().adminUser(this.user.get("id"));
    if (success) {
      displaySuccess(`${this.user.get("name")} is now administrator`);
    }
    this.actualize();
  }

  async onUserUnAdmin() {
    const success = await currentUser().unAdminUser(this.user.get("id"));
    if (success) {
      displaySuccess(`${this.user.get("name")} is not administrator anymore`);
    }
    this.actualize();
  }

  async onUserBan() {
    const success = await currentUser().banUser(this.user.get("id"));
    if (success) {
      displaySuccess(`${this.user.get("name")} has been banned`);
    }
    this.actualize();
  }

  async onUserUnban() {
    const success = await currentUser().unbanUser(this.user.get("id"));
    if (success) {
      displaySuccess(`${this.user.get("name")} has been unbanned`);
    }
    this.actualize();
  }

  onClickSendDm() {
    eventBus.trigger("chat:open");
    eventBus.trigger("chat:go-to-dm", this.user.get("id"));
  }

  async onAddFriend() {
    const success = await this.user.addFriend();

    if (success) {
      displaySuccess(
        `Your invitation has been sent to ${this.user.get("name")}`
      );
      this.actualize();
    }
  }

  async onRemoveFriend() {
    const success = await this.user.removeFriend();

    if (success) {
      displaySuccess(`Your are no longer friend with ${this.user.get("name")}`);
      this.actualize();
    }
  }

  onRequestClicked() {
    const requestsView = new RequestsView({
      model: this.user,
    });

    requestsView.render();
  }

  onFriendsClicked() {
    const friendsView = new FriendsView({
      model: this.user,
    });

    friendsView.render();
  }

  onFetchError() {
    Backbone.history.navigate("/not-found", { trigger: true });
  }

  render() {
    const ready = !!this.user.get("name");

    if (!ready) {
      return this.renderLoadingPage();
    }

    const template = $("#userPageTemplate").html();
    const html = Mustache.render(template, {
      ...this.user.toJSON(),
      created_at: moment(this.user.get("created_at"))?.format("DD/MM/YYYY"),
      has_guild: !!this.user.get("guild"),
      is_current_user: this.user.get("id") === currentUser().get("id"),
      no_relation:
        !this.user.get("is_friend") &&
        !this.user.get("has_received_friend") &&
        !this.user.get("has_requested_friend"),
      cur: currentUser().get("id"),
      is_admin: currentUser().get("admin"),
    });
    this.$el.html(html);

    if (this.user.get("friend_requests")) {
      if (this.user.get("friend_requests").length > 0) {
        this.$("#request-btn").addClass("animate-bounce");
      }
    }

    if (
      this.user.get("won_tournaments") &&
      this.user.get("won_tournaments").length != 0
    ) {
      var trophiesView = new TrophiesView({
        tournaments: this.user.get("won_tournaments"),
      });
      this.renderNested(trophiesView, "#trophies");
    } else {
      this.$("#tour-trophies").hide();
    }

    var gameHistoryView = new GameHistoryView({
      user: this.user,
    });
    this.renderNested(gameHistoryView, "#gamehistory");

    return this;
  }

  actualize() {
    this.user.fetch({ error: this.onFetchError });
  }
}
