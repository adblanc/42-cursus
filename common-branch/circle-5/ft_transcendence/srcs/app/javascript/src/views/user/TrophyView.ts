import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "../../lib/BaseView";
import Tournament from "src/models/Tournament";
import { displaySuccess } from "src/utils";

type Options = Backbone.ViewOptions & { model: Tournament};

export default class TrophyView extends BaseView {
  model: Tournament;

  constructor(options?: Options) {
    super(options);
	this.model = options.model;
  }

  render() {
    const template = $("#trophyTemplate").html();
	const html = Mustache.render(template, this.model.toJSON());
    this.$el.html(html);
    return this;
  }
}