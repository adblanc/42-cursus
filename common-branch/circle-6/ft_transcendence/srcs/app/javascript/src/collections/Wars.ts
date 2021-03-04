import Backbone from "backbone";
import { BASE_ROOT } from "src/constants";
import War from "../models/War";

export default class Wars extends Backbone.Collection<War> {
  constructor() {
    super();

    this.model = War;
    this.url = `${BASE_ROOT}/wars`;
  }
}
