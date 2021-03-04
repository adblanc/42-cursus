import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "src/lib/BaseView";
import PublicRoom from "src/models/PublicRoom";
import JoinPublicChannelView from "./JoinPublicChannelView";

export default class PublicRoomView extends BaseView<PublicRoom> {
  constructor(options?: Backbone.ViewOptions<PublicRoom>) {
    super(options);

    if (!this.model) {
      throw Error("Please provide a PublicRoom model.");
    }

    this.listenTo(this.model, "change", this.render);
  }

  events() {
    return {
      "click .room-name": this.onClick,
    };
  }

  onClick() {
    const joinPublicChannelView = new JoinPublicChannelView({
      model: this.model,
    });

    joinPublicChannelView.render();
  }

  render() {
    const template = $("#roomTemplate").html();
    const html = Mustache.render(template, this.model.toJSON());
    this.$el.html(html);

    return this;
  }
}
