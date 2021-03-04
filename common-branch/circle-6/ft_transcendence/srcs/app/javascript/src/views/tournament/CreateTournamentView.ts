import Backbone from "backbone";
import Mustache from "mustache";
import ModalView from "../ModalView";
import Tournament from "src/models/Tournament";
import { displaySuccess } from "src/utils/toast";

const flatpickr = require("flatpickr");
require("flatpickr/dist/flatpickr.css");

export default class CreateTournamentView extends ModalView<Tournament> {
  fp_start: typeof flatpickr;
  fp_end: typeof flatpickr;

  constructor(options?: Backbone.ViewOptions<Tournament>) {
    super(options);

    this.listenTo(this.model, "change", this.render);
  }

  events() {
    return { ...super.events(), "click #input-tournament-submit": "onSubmit" };
  }

  async onSubmit(e: JQuery.Event) {
    e.preventDefault();

    const dateTimeStart = this.fp_start.selectedDates[0];
    const dateTimeEnd = this.fp_end.selectedDates[0];

    const attrs = {
      name: this.$("#input-tournament-name").val() as string,
      trophy: (this.$("#input-trophy-img")[0] as HTMLInputElement).files?.item(
        0
      ),
      registration_start: dateTimeStart,
      registration_end: dateTimeEnd,
    };

    if (!attrs.trophy) delete attrs.trophy;

    const success = await this.model.createTournament(attrs);
    if (success) {
      this.tournamentSaved();
    }
  }

  tournamentSaved() {
    displaySuccess("Tournament successfully created.");
    this.closeModal();
    this.model.fetch();
    Backbone.history.navigate(`tournaments/${this.model.get("id")}`, {
      trigger: true,
    });
  }

  dismiss = (e: JQuery.ClickEvent) => {
    if ($(e.target).closest(".flatpickr-wrapper").length === 0) {
      this.fp_start.close();
      this.fp_end.close();
    }
  };

  render() {
    super.render();
    const template = $("#tournamentFormTemplate").html();
    const html = Mustache.render(template, this.model.toJSON());
    this.$content.html(html);

    this.fp_start = flatpickr(
      this.$("#input-start-date"),
      {
        enableTime: true,
        dateFormat: "Y-m-d H:i",
        minuteIncrement: 1,
        static: true,
        minDate: new Date(),
      },
      this
    );
    this.fp_end = flatpickr(this.$("#input-end-date"), {
      enableTime: true,
      dateFormat: "Y-m-d H:i",
      minuteIncrement: 1,
      static: true,
      minDate: new Date(),
    });

    this.$content.on("click", this.dismiss);

    return this;
  }
}
