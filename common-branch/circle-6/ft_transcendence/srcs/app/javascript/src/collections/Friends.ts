import Backbone from "backbone";
import User from "../models/User";

export default class Friends extends Backbone.Collection<User> {
  constructor() {
    super();

    this.model = User;
  }
}
