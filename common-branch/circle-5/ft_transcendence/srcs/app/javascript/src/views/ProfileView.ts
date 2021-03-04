import Backbone from "backbone";
import Mustache from "mustache";
import Profile from "../models/Profile";
import ModifyProfileView from "./ModifyProfileView";

export default class ProfileView extends Backbone.View<Profile> {
  constructor(options?: Backbone.ViewOptions<Profile>) {
    super(options);

    this.listenTo(this.model, "change", this.render);
  }

  events() {
    return {
      "click #btn-profile": "onProfileClicked",
    };
  }

  onProfileClicked() {
    const modifyProfileView = new ModifyProfileView({
      model: this.model,
    });

    modifyProfileView.render();
  }

  render() {
    const template = $("#profileTemplate").html();
    const html = Mustache.render(template, this.model.toJSON());
    this.$el.html(html);

    return this;
  }
}
