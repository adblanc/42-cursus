import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "../ModalView";
import Guild from "src/models/Guild";
import { displaySuccess, displayError } from "src/utils/toast";

export default class ModifyGuildView extends ModalView<Guild> {
  constructor(options?: Backbone.ViewOptions<Guild>) {
    super(options);

    /*maybe i don't need this*/
    this.listenTo(this.model, "change", this.render);
    this.listenTo(this.model, "add", this.render);
  }

  events() {
    return {
      ...super.events(),
      "click #input-guild-submit": "onSubmit",
      ...super.events(),
      "click #destroy-guild": "onDestroy",
    };
  }

  async onDestroy(e: JQuery.Event) {
    e.preventDefault();

	await this.model.destroy({
		success : function() { displaySuccess("Guild successfully destroyed."); },
		error : function() { displayError("Guild can't be destroyed."); },
		wait: true,
	});
	this.closeModal();
	Backbone.history.navigate("/", { trigger: true });
  }

  async onSubmit(e: JQuery.Event) {
    e.preventDefault();
    let acr = this.$("#input-guild-ang").val() as string;
    const attrs = {
      name: this.$("#input-guild-name").val() as string,
      ang: acr.toUpperCase(),
      img: (this.$("#input-guild-img")[0] as HTMLInputElement).files?.item(0),
    };

    if (!attrs.img) delete attrs.img;

    const success = await this.model.modifyGuild(attrs);

    if (success) {
      displaySuccess("Guild successfully updated.");
      this.closeModal();
      this.model.fetch();
    }
  }

  render() {
    super.render();
    const template = $("#guildEditFormTemplate").html();
    const html = Mustache.render(template, this.model.toJSON());
    this.$content.html(html);
    return this;
  }
}
