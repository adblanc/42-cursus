import Mustache from "mustache";
import Backbone from "backbone";
import BaseView from "src/lib/BaseView";
import Tournament from "src/models/Tournament"
import CreateTournamentView from "./CreateTournamentView"
import TourListView from "./TourListView"
import Tournaments from "src/collections/Tournaments";
import { currentUser } from "src/models/Profile";
import { eventBus } from "src/events/EventBus";

export default class TempTournamentView extends BaseView {
	collection: Tournaments;
	current: Tournaments;

  constructor(options?: Backbone.ViewOptions) {
	super(options);

	this.collection = new Tournaments();
	this.listenTo(this.collection, "add", this.render);
	this.listenTo(this.collection, "remove", this.render);
    this.listenTo(this.collection, "change", this.render);
    this.listenTo(this.collection, "sort", this.render);
    this.collection.fetch();
	this.collection.sort();

	this.current = currentUser().get("current_tournaments");
	this.listenTo(currentUser(), "change", this.render);
	this.listenTo(eventBus, "tournament:change", this.updateTournament);
	this.listenTo(eventBus, "tournament:new", this.updateTournaments);
  }

  updateTournament(id: string) {
  	this.collection.get(id).fetch();
  }

  updateTournaments() {
  	this.collection.fetch();
  }

  events() {
    return {
      "click #create-tour-btn": "onCreateClicked",
    };
  }

  onCreateClicked() {
    const tournament = new Tournament();
    const createTournamentView = new CreateTournamentView({
      model: tournament,
    });

    createTournamentView.render();
  }


  render() {
    const template = $("#tempTournamentTemplate").html();
    const html = Mustache.render(template, {
		admin: currentUser().get("admin") == true
	});
	this.$el.html(html);

	if (this.current != undefined && this.current.length == 0) {
		this.$("#no-part").show();
	}
	else if (this.current != undefined) {
		this.current.forEach(function (item) {
			var tourListView = new TourListView({
				model: item,
				mine: true,
			});
			this.$("#my-participations").append(tourListView.render().el);
		}, this);
	}

	var pend = 0;
	var reg = 0;
	var fin = 0;
	this.collection.forEach(function (item) {
		var tourListView = new TourListView({
			model: item,
			mine: false,
		});
		if (item.get("status") == "registration") {
			this.$("#list-open").append(tourListView.render().el);
			reg++;
		}
		else if (item.get("status") == "pending") {
			this.$("#list-upcoming").append(tourListView.render().el);
			pend++;
		}
		else if (item.get("status") != "finished") {
			this.$("#list-raging").append(tourListView.render().el);
			fin++;
		}
	}, this);

	if (reg == 0)
		this.$("#none-open").show();
	if (pend == 0)
		this.$("#none-upcoming").show();
	if (fin == 0)
		this.$("#none-raging").show();

    return this;
  }

}
