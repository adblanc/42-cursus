import Backbone from "backbone";
import Mustache from "mustache";
import Room from "src/models/Room";
import { displaySuccess } from "src/utils";
import ModalView from "src/views/ModalView";
import RoomUsersView from "./RoomUsersView";
import ConfirmationModalView from "src/views/ConfirmationModalView";

export default class ManageRoomView extends ModalView<Room> {
  constructor(options?: Backbone.ViewOptions<Room>) {
    super(options);

    if (!this.model)
      throw Error("Please provide a room model to ModifyProfileView");

    this.listenTo(this.model.get("users"), "update", this.render);
  }

  events() {
    return {
      ...super.events(),
      "click #room-submit": this.onSubmit,
      "click #room-delete": this.askDeleteConfirmation,
    };
  }

  async onSubmit(e: JQuery.ClickEvent) {
    e.preventDefault();

    const password = this.$("#input-room-password").val() as string;

    const success = await this.model.modifyPassword(password);

    if (success) {
      displaySuccess(
        `${this.model.get("name")}'s password successfully ${
          password.length === 0 ? "removed" : "changed"
        }.`
      );
      this.closeModal();
    }
  }

  askDeleteConfirmation(e: JQuery.ClickEvent) {
    const question = `Are you sure you want to delete ${this.model.get(
      "name"
    )} ?`;

    const confirmationView = new ConfirmationModalView({
      question,
      onYes: () => this.onDelete(e),
    });

    confirmationView.render();
  }

  async onDelete(e: JQuery.ClickEvent) {
    e.preventDefault();

    const success = await this.model.delete();

    if (success) {
      displaySuccess(
        `${this.model.get("name")}'s has been successfully deleted.`
      );
      this.closeModal();
    }
  }

  render() {
    super.render();
    const template = $("#manage-room-template").html();

    const html = Mustache.render(template, {
      ...this.model.toJSON(),
    });

    this.$content.html(html);

    this.renderNested(
      new RoomUsersView({
        model: this.model,
      }),
      "#room-users-list"
    );

    return this;
  }
}
