import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "./ModalView";
import Profile from "../models/Profile";

type Options = Backbone.ViewOptions<Profile> & {
  onYes?: () => void;
  onNo?: () => void;
  question: string;
};

export default class ConfirmationModalView extends ModalView {
  onYes?: () => void;
  onNo?: () => void;
  question: string;

  constructor(options: Options) {
    super(options);

    this.onYes = options.onYes;
    this.onNo = options.onNo;
    this.question = options.question;
  }

  events() {
    return {
      ...super.events(),
      "click #yes-btn": () => {
        if (this.onYes) {
          this.onYes();
        }
        this.close();
      },
      "click #no-btn": () => {
        if (this.onNo) {
          this.onNo();
        }
        this.close();
      },
    };
  }

  render() {
    super.render();
    const template = $("#confirmation-modal-template").html();
    const html = Mustache.render(template, {
      question: this.question,
    });
    this.$content.html(html);
    return this;
  }
}
