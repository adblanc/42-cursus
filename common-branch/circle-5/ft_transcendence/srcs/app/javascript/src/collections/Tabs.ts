import Backbone from "backbone";
import Tab from "src/models/Tab";

export default class Tabs extends Backbone.Collection<Tab> {
  constructor() {
    super();

    this.model = Tab;
  }
}
