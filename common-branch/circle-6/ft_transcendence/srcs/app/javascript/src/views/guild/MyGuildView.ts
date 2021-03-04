import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import CreateGuildView from "./CreateGuildView";
import { currentUser } from "src/models/Profile";
import Guild from "src/models/Guild";
import Guilds from "src/collections/Guilds";
import Profile from "src/models/Profile";
import { displaySuccess } from "src/utils";

type Options = Backbone.ViewOptions & { collection: Guilds };

export default class MyGuildView extends BaseView {
  collection: Guilds;

  constructor(options?: Options) {
    super(options);

    this.collection = options.collection;

    this.listenTo(currentUser(), "change", this.render);
  }

  events() {
    return {
      "click #create-btn": "onCreateClicked",
      "click #withdraw-btn": "onWithdrawClicked",
    };
  }

  onCreateClicked() {
    const guild = new Guild();
    const createGuildView = new CreateGuildView({
      model: guild,
      collection: this.collection,
    });

    createGuildView.render();
  }

  async onWithdrawClicked() {
    const success = await currentUser().get("pending_guild").withdraw();

    if (success) {
      this.guildWithdraw();
    }
  }

  guildWithdraw() {
    displaySuccess(
      `You have withdrawn your request to join ${currentUser()
        .get("pending_guild")
        .get("name")}.`
    );
    currentUser().fetch();
  }

  render() {
    if (currentUser().get("guild")) {
      const template = $("#withGuildTemplate").html();
      const html = Mustache.render(template, currentUser().toJSON());
      this.$el.html(html);
    } else if (currentUser().get("pending_guild")) {
      const template = $("#withPendingGuildTemplate").html();
      const html = Mustache.render(template, currentUser().toJSON());
      this.$el.html(html);
    } else {
      const template = $("#noGuildTemplate").html();
      const html = Mustache.render(template, currentUser().toJSON());
      this.$el.html(html);
    }

    return this;
  }
}
