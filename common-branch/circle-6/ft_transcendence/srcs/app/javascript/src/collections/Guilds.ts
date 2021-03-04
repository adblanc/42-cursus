import Backbone from "backbone";
import { BASE_ROOT } from "src/constants";
import Guild from "src/models/Guild";

export default class Guilds extends Backbone.Collection<Guild> {
  constructor() {
    super();
    this.model = Guild;
    this.url = `${BASE_ROOT}/guilds`;

    this.comparator = function (model) {
      return -model.get("points");
    };
  }

  get maximumPoints() {
    return this.max((g) => g.get("points")).get("points");
  }
}
