import Backbone from "backbone";
import WarTime from "src/models/WarTime";

export default class WarTimes extends Backbone.Collection<WarTime> {
  constructor() {
    super();

    this.model = WarTime;
  }
}
