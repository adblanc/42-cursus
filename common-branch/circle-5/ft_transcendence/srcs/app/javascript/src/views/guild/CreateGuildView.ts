import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "../ModalView";
import Guild from "src/models/Guild";
import { displaySuccess } from "src/utils/toast";
import { generateAcn } from "src/utils/acronym";
import { displayError } from "src/utils";
import { currentUser } from "src/models/Profile";

export default class CreateGuildView extends ModalView<Guild> {
  list: string[];

  constructor(options?: Backbone.ViewOptions<Guild>) {
    super(options);

    var tmp = [];
    this.listenTo(this.model, "change", this.render);
    this.listenTo(this.model, "add", this.render);

    this.collection.forEach(function (item) {
      tmp.push(item.get("ang"));
    });
    this.list = tmp;
  }

  events() {
    return { ...super.events(), "click #input-guild-submit": "onSubmit" };
  }

  async onSubmit(e: JQuery.Event) {
    e.preventDefault();

    const name = this.$("#input-guild-name").val() as string;

    if (!name) {
      return displayError("Guild name can't be blank.");
    }

    var acn = generateAcn(name, this.list) as string;
    if (acn == "error") {
      displayError(
        "Acronym generation error : your chosen guild name is too similar to existing guild. Please choose another name."
      );
      acn = "";
    } else {
      const attrs = {
        name,
        ang: acn,
        img: (this.$("#input-guild-img")[0] as HTMLInputElement).files?.item(0),
      };

      if (!attrs.img) delete attrs.img;

      const success = await this.model.createGuild(attrs);
      if (success) {
        this.guildSaved();
      }
    }
  }

  guildSaved() {
    displaySuccess("Guild successfully created.");
    this.closeModal();

    currentUser().set({ guild: this.model });
    Backbone.history.navigate(`guild/${this.model.get("id")}`, {
      trigger: true,
    });
  }

  render() {
    super.render();
    const template = $("#guildFormTemplate").html();
    const html = Mustache.render(template, this.model.toJSON());
    this.$content.html(html);
    return this;
  }
}
