import Backbone from "backbone";
import Profile from "../models/Profile";

export default class Profiles extends Backbone.Collection<Profile> {
  constructor() {
    super();

	this.model = Profile;
	
	this.comparator = function(model) {
		return -model.get('contribution');
	}
  }
}
