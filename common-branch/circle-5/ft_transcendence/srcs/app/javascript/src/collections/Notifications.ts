import Backbone from "backbone";
import Notification from "src/models/Notification";

export default class Notifications extends Backbone.Collection<Notification> {
	constructor() {
	  super();
  
	  this.model = Notification;

	  this.comparator = function (model) {
		return model.get("created_at");
	  };
	}

	getUnreadNb() {
		var nb = 0;
		this.forEach(function (item) {
			if (!item.get("read_at")) {
				nb++;
			}
		});
		return nb;
  }
}