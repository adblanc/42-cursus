import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import War from "src/models/War";
import Guild from "src/models/Guild";
import moment from "moment";

type Options = Backbone.ViewOptions & { model: War; guild: Guild };

export default class NodeView extends BaseView {
  model: War;
  guild: Guild;

  constructor(options?: Options) {
    super(options);

    this.model = options.model;
    this.guild = options.guild;
  }

  render() {
    const war = {
      ...this.model.toJSON(),
      start: moment(this.model.get("start")).format("MM/DD/YY"),
      end: moment(this.model.get("end")).format("MM/DD/YY"),
    };

    const template = $("#warNodeTemplate").html();
    const html = Mustache.render(template, {
      war: war,
      ang: this.guild.get("ang"),
      curr: this.model.get("status") === "started",
      tie: this.model.get("winner") === "tie",
    });
    this.$el.html(html);

    return this;
  }
}
