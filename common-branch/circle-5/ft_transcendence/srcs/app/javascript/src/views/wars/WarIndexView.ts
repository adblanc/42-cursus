import Backbone from "backbone";
import Mustache from "mustache";
import BaseView from "src/lib/BaseView";
import Wars from "src/collections/Wars";
import WarBoardView from "./WarBoardView";
import MyWarView from "./MyWarView";

export default class WarIndexView extends BaseView {
  wars: Wars;
  warBoardView: WarBoardView;
  myWarView: MyWarView;

  constructor(options?: Backbone.ViewOptions) {
    super(options);
  }

  render() {
    const template = $("#warIndexTemplate").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);

    this.renderWarBoardView();
    this.renderMyWarView();

    return this;
  }

  renderWarBoardView() {
    this.warBoardView = new WarBoardView();
    this.renderNested(this.warBoardView, "#board");
  }

  renderMyWarView() {
    this.myWarView = new MyWarView();
    this.renderNested(this.myWarView, "#mywar");
  }
}
