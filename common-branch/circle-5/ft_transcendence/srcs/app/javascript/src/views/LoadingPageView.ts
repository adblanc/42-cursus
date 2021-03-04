import Mustache from "mustache";
import Backbone from "backbone";

export default class LoadingPageView extends Backbone.View {
  render() {
    const template = $("#loading-page-template").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);

    return this;
  }
}
