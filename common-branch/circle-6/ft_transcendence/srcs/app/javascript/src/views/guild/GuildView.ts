import Backbone from "backbone";
import Mustache from "mustache";
import InfoView from "./InfoView";
import MembersView from "./MembersView";
import Guild from "src/models/Guild";
import BaseView from "src/lib/BaseView";

type Options = Backbone.ViewOptions & { guild: Guild };

export default class GuildView extends BaseView {
  infoView: InfoView;
  membersView: MembersView;
  guild: Guild;
  ready: boolean;

  constructor(options?: Options) {
    super(options);

    this.guild = options.guild;

    this.infoView = new InfoView({
      guild: this.guild,
    });
    this.membersView = new MembersView({
      guild: this.guild,
    });

    this.ready = false;
    this.guild.fetch({
      error: () => {
        Backbone.history.navigate("/not-found", { trigger: true });
      },
      success: () => {
        this.ready = true;
        this.render();
      },
    });

    this.listenTo(this.guild, "change", this.render);
  }

  render() {
    if (!this.ready) {
      return this.renderLoadingPage();
    }

    const template = $("#guildPageTemplate").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);

    this.renderNested(this.infoView, "#info");
    this.renderNested(this.membersView, "#members");

    return this;
  }
}
