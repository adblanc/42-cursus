import Backbone from "backbone";
import User from "../models/User";
import { BASE_ROOT } from "src/constants";

export default class RankedUsers extends Backbone.Collection<User> {
  constructor() {
    super();

	this.model = User;
	this.url = `${BASE_ROOT}/users`;
	
	this.comparator = function(model) {
		return model.get('ladder_rank');
	}
  }
}
