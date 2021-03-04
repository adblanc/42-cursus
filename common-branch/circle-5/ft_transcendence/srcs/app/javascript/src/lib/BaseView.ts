import Backbone from "backbone";
import LoadingPageView from "src/views/LoadingPageView";

export type View<T> = Omit<Backbone.View, "events"> & {
  events: () => Record<string, keyof View<T>>;
};

export default class BaseView<
  TModel extends Backbone.Model = Backbone.Model
> extends Backbone.View<TModel> {
  onClose?: () => void;

  constructor(options?: Backbone.ViewOptions<TModel>) {
    super(options);
  }

  verifyModelExists() {
    if (!this.model) {
      throw Error("Please pass a model to this view");
    }
  }

  verifyCollectionExists() {
    if (!this.collection) {
      throw Error("Please pass a collection to this view");
    }
  }

  getChildrenLength(selector: string) {
    return this.$(selector).children().length;
  }

  renderNested(view: Backbone.View, selector: string) {
    const $element = this.$(selector);

    view.setElement($element).render();
  }

  appendNested(view: Backbone.View, selector: string) {
    const $element = this.$(selector);

    $element.append(view.render().el);
  }

  preprendNested(view: Backbone.View, selector: string) {
    const $element = this.$(selector);

    $element.prepend(view.render().el);
  }

  close() {
    if (this.onClose) {
      this.onClose();
    }
    this.remove();
    this.unbind();
  }

  renderLoadingPage() {
    const loadingView = new LoadingPageView();

    this.$el.html(loadingView.render().$el.html());

    return this;
  }
}
