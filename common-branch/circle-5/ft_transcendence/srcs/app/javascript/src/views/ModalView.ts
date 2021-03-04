import Backbone from "backbone";
import Mustache from "mustache";
import { eventBus } from "src/events/EventBus";
import BaseView from "src/lib/BaseView";
import { closeAllModal, navigate } from "src/utils";

export default class ModalView<
  TModel extends Backbone.Model = Backbone.Model
> extends BaseView<TModel> {
  $content: any;
  modalId: number;

  constructor(options?: Backbone.ViewOptions<TModel>) {
    super(options);

    this.$content = undefined;
    this.modalId = this.generateModalId();
  }

  generateModalId() {
    return $(".modal-backdrop").length;
  }

  events() {
    return {
      "click .modal-backdrop": this.close,
      "click .modal-container": this.dismissClick,
      "click #close-modal": this.close,
      "click a": this.onLinkOpen,
    };
  }

  onLinkOpen(e: JQuery.ClickEvent) {
    closeAllModal();
    eventBus.trigger("chat:close");

    navigate(e);
  }

  dismissClick(e: JQuery.Event) {
    e.stopPropagation();
  }

  closeModal() {
    this.close();
  }

  render() {
    const template = $("#modalTemplate").html();
    const html = Mustache.render(template, {
      id: this.modalId,
    });
    this.$el.html(html);
    $("body").append(this.$el);

    this.$content = $(`#modal-content-${this.modalId}`);

    return this;
  }
}
