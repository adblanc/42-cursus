import Backbone from "backbone";
import Tournament from "src/models/Tournament";
import { BASE_ROOT } from "src/constants";
import consumer from "channels/consumer";
import { eventBus } from "src/events/EventBus";

export default class Tournaments extends Backbone.Collection<Tournament> {
	static GLOBAL_CHANNEL: ActionCable.Channel = undefined;

	constructor() {
		super();
		this.model = Tournament;
		this.url = `${BASE_ROOT}/tournaments`;

		this.comparator = function(model) {
			return model.get('registration_start');
		}

		Tournaments.GLOBAL_CHANNEL ||= consumer.subscriptions.create({
				channel: "TournamentsGlobalChannel"
			}, {
				received(data) {
					eventBus.trigger("tournament:new");
			}
		});
	}
}
