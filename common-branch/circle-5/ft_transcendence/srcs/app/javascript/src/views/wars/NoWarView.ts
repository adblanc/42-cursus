import Mustache from "mustache";
import BaseView from "src/lib/BaseView";

export default class NoWarView extends BaseView {
  render() {
    const template = $("#noWarTemplate").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);

    return this;
  }
}
