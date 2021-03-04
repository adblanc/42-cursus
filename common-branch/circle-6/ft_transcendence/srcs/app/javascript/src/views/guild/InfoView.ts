import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "src/lib/BaseView";
import { currentUser } from "src/models/Profile";
import Guild from "src/models/Guild";
import ModifyGuildView from "./ModifyGuildView";
import DeclareWarView from "../wars/DeclareWarView";
import { displaySuccess } from "src/utils";
import War from "src/models/War";
import ConfirmationModalView from "../ConfirmationModalView";

type Options = Backbone.ViewOptions & { guild: Guild };

export default class InfoView extends BaseView {
  guild: Guild;

  constructor(options?: Options) {
    super(options);

    this.guild = options.guild;

    this.listenTo(this.guild, "change", this.render);
    this.listenTo(this.guild.get("members"), "update", this.render);
    this.listenTo(currentUser(), "change", this.render);
    this.listenTo(currentUser().get("guild"), "change", this.render);
  }

  events() {
    return {
      "click #edit-btn": this.onEditClicked,
      "click #edit-img": this.onEditClicked,
      "click #quit-btn": this.askConfirmationQuitGuild,
      "click #join-btn": this.onJoinClicked,
      "click #withdraw-btn": this.onWithdrawClicked,
      "click #war-btn": this.onWarClicked,
    };
  }

  onEditClicked() {
    const modifyGuildView = new ModifyGuildView({
      model: this.guild,
    });

    modifyGuildView.render();
  }

  askConfirmationQuitGuild() {
    const confirmationView = new ConfirmationModalView({
      question: `Are you sure you want to ${
        this.guild.get("members").size() === 1 ? "destroy" : "quit"
      } ${this.guild.get("name")} `,
      onYes: this.onQuitClicked,
    });

    confirmationView.render();
  }

  onQuitClicked = async () => {
    const success = await this.guild.quit();
    if (success) {
      this.guildQuit();
    }
  };

  guildQuit() {
    displaySuccess(`You successfully left ${this.guild.get("name")}.`);
    this.guild.fetch();
    currentUser().fetch();
    if (this.guild.get("members").length == 0) {
      displaySuccess(
        `You were the only member of ${this.guild.get(
          "name"
        )}, so the guild was destroyed.`
      );
      return Backbone.history.navigate("/", { trigger: true });
    } else if (currentUser().get("guild_role") == "Owner") {
      displaySuccess(
        `Your owner privileges were transferred to ${this.guild.get(
          "name"
        )}'s oldest member.`
      );
    }
  }

  async onJoinClicked() {
    const success = await this.guild.join();
    if (success) {
      this.guildJoin();
    }
  }

  guildJoin() {
    displaySuccess(
      `You have sent a join request to ${this.guild.get("name")}. `
    );
    this.guild.fetch();
    currentUser().fetch();
  }

  async onWithdrawClicked() {
    const success = await this.guild.withdraw();

    if (success) {
      this.guildWithdraw();
    }
  }

  guildWithdraw() {
    displaySuccess(
      `You have withdrawn your request to join ${this.guild.get("name")}. `
    );
    this.guild.fetch();
    currentUser().fetch();
  }

  onWarClicked() {
    const war = new War();
    const declareWarView = new DeclareWarView({
      model: war,
      guild: this.guild,
    });
    currentUser().fetch();
    declareWarView.render();
  }

  render() {
    const template = $("#infoTemplate").html();
    const html = Mustache.render(template, {
      ...this.guild.toJSON(),
      isAGuildOwner: currentUser().get("guild")?.get("isOwner"),
      hasAGuild: !!currentUser().get("guild"),
    });
    this.$el.html(html);

    if (this.guild.get("atWar")) {
      this.$("#war-btn").addClass("btn-war-disabled");
      this.$("#war-btn").html("This Guild is at war");
    } else if (this.guild.get("warInitiator")) {
      this.$("#war-btn").addClass("btn-war-disabled");
      this.$("#war-btn").html("This Guild has initiated a war");
    } else if (currentUser().get("guild")) {
      if (currentUser().get("guild").get("atWar")) {
        this.$("#war-btn").addClass("btn-war-disabled");
        this.$("#war-btn").html("Your Guild is at war");
      } else if (currentUser().get("guild").get("warInitiator")) {
        this.$("#war-btn").addClass("btn-war-disabled");
        this.$("#war-btn").html("Your Guild has initiated a war");
      }
    }

    if (currentUser().get("pending_guild")) {
      if (
        currentUser().get("pending_guild").get("id") === this.guild.get("id")
      ) {
        this.$("#join-btn").css("font-size", 15 + "px");
        this.$("#join-btn").html("Withdraw your join request");
        this.$("#join-btn").attr("id", "withdraw-btn");
      } else {
        this.$("#join-btn").addClass("btn-join-disabled");
        this.$("#join-btn").html("You have asked to join another guild");
      }
    }

    return this;
  }
}
