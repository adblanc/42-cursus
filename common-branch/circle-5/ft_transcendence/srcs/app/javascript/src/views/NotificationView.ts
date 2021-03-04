import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../lib/BaseView";
import Notification from "src/models/Notification";
import moment from "moment";
import { eventBus } from "src/events/EventBus";

type Options = Backbone.ViewOptions<Notification> & {
  page: boolean;
};

export default class ItemView extends BaseView<Notification> {
  momentString: string;
  page: boolean;

  constructor(options?: Options) {
    super(options);

    this.page = options.page;

    this.listenTo(this.model, "change", this.render);
  }

  events() {
    return {
      "click #trigger-notif": this.triggerNotif,
    };
  }

  triggerNotif() {
    if (this.model.get("notification_type") === "dm-creation") {
      eventBus.trigger("chat:open");
      eventBus.trigger("notifications:close");
    }
  }

  render() {
    const notif = {
      ...this.model.toJSON(),
      created_at: moment(this.model.get("created_at")).format(
        "MMM Do YY, h:mm a"
      ),
    };

    const template = $("#notifTemplate").html();
    const html = Mustache.render(template, notif);
    this.$el.html(html);

    if (this.page) {
      this.$("#notif-item").addClass("notifpage");
    }

    return this;
  }
}
