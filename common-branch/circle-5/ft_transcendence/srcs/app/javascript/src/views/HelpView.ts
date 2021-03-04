import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "src/lib/BaseView";
import { displaySuccess } from "src/utils";

export default class HelpView extends BaseView {
  
  constructor(options?: Backbone.ViewOptions) {
    super(options);
  }

  render() {
    const template = $("#help").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);
    return this;
  }
}