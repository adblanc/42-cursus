import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../lib/BaseView";
import Profile, { currentUser } from "src/models/Profile";
import NotificationView from "./NotificationView";
import { eventBus } from "src/events/EventBus";
import { navigate } from "src/utils";

export default class NotificationsView extends BaseView {
  profile: Profile;

  constructor(options?: Backbone.ViewOptions) {
    super(options);

    this.profile = currentUser();

    this.listenTo(this.profile.notifications, "add", this.render);
    this.listenTo(eventBus, "notifications:open", this.toggleNotifications);
    this.listenTo(eventBus, "notifications:close", this.hideNotif);
  }

  events() {
    return {
      "click #see-btn": this.onSeeClicked,
      "click #content": this.onSeeClicked,
      "click #notif-backdrop": this.onBackdropClicked,
      "click .notif-container": this.dismissClick,
      "click a": navigate,
    };
  }

  onSeeClicked() {
    this.toggleNotifications();
  }

  toggleNotifications() {
    this.$el.toggleClass("invisible");
  }

  onBackdropClicked(e: JQuery.ClickEvent) {
    this.dismissNotif(e);
  }

  hideNotif() {
    if (!this.$el.hasClass("invisible")) {
      this.toggleNotifications();
    }
  }

  dismissNotif = (e: JQuery.ClickEvent) => {
    if ($(e.target).closest("#notifications-container").length === 0) {
      this.hideNotif();
    }
  };

  dismissClick(e: JQuery.ClickEvent) {
    e.stopPropagation();
  }

  render() {
    const template = $("#notificationsTemplate").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);

    const $element = this.$("#notifications-container");

    if (this.profile.notifications.length === 0) {
      this.$("#empty").show();
      this.$("#see-btn").hide();
    }

    this.profile.notifications
      .slice(
        this.profile.notifications.length - 5,
        this.profile.notifications.length
      )
      .forEach(function (item) {
        var notificationView = new NotificationView({
          model: item,
          page: false,
        });
        $element.prepend(notificationView.render().el);
      });

    return this;
  }
}
