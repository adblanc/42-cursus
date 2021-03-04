import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "./ModalView";
import Profile from "../models/Profile";
import { displaySuccess } from "src/utils";
import { eventBus } from "src/events/EventBus";

export default class ModifyProfileView extends ModalView<Profile> {
  constructor(options?: Backbone.ViewOptions<Profile>) {
    super(options);

    if (!this.model)
      throw Error("Please provide a profile model to ModifyProfileView");
  }

  events() {
    return { ...super.events(), "click #input-profile-submit": "onSubmit" };
  }

  async onSubmit(e: JQuery.Event) {
    e.preventDefault();
    const attrs = {
      name: this.$("#input-profile-name").val() as string,
      email: this.$("#input-profile-email").val() as string,
      two_fact_auth: this.$("#input-profile-tfa").prop('checked') as boolean,
      avatar: (this.$(
        "#input-profile-avatar"
      )[0] as HTMLInputElement).files?.item(0),
    };

    if (!attrs.avatar) delete attrs.avatar;

    const success = await this.model.modifyProfil(attrs);

    if (success) {
      displaySuccess("Profile successfully changed.");
	  eventBus.trigger("profile:change");
      this.closeModal();
      this.model.fetch();
    }
  }

  render() {
    super.render();
    const template = $("#profileFormTemplate").html();
    const html = Mustache.render(template, this.model.toJSON());
    this.$content.html(html);
    return this;
  }
}
