import Backbone from "backbone";
import Mustache from "mustache";
import Guild from "src/models/Guild";
import BaseView from "src/lib/BaseView";
import Wars from "src/collections/Wars";
import War from "src/models/War";
import NodeView from "./NodeView";

type Options = Backbone.ViewOptions & { guild: Guild };

export default class WarHistoryView extends BaseView {
  guild: Guild;
  collection: Wars;
  max: number;
  count: number;

  constructor(options?: Options) {
    super(options);

	this.guild = options.guild;
	this.collection = this.guild.get("wars");
	this.max = 5;

    this.guild.fetch({
      error: () => {
        Backbone.history.navigate("/not-found", { trigger: true });
      },
    });

    this.listenTo(this.guild, "change", this.render);
  }

  events() {
    return {
      "click #pending-btn": "onPendingClicked",
      "click #load-more": "onLoadMore",
    };
  }

  renderWar(war: War) {
	var nodeView = new NodeView({
		model: war,
		guild: this.guild,
	});
    this.$("#listing").append(nodeView.render().el);
  }

  onLoadMore() {
    var wars = this.collection.models.slice(this.count, this.count + this.max);
    if (wars.length) {
      wars.forEach(function (item) {
		if (item.get("status") != "pending" && item.get("status") != "confirmed") {
			this.renderWar(item);
		}
      }, this);
      this.count += wars.length;
    }
    if (this.count == this.collection.length) {
      this.$("#load-more").hide();
    }
  }

  render() {
    const template = $("#warHistoryTemplate").html();
    const html = Mustache.render(template, this.guild.toJSON());
	this.$el.html(html);
	
	const $element = this.$("#listing");

	if (this.collection.isEmpty() || (this.collection.length == 1 && this.guild.get("pendingWar"))) {
		this.$("#no-war").show();
	}

	var wars = this.collection.first(this.max);
    wars.forEach(function (item) {
		if (item.get("status") != "pending" && item.get("status") != "confirmed") {
			this.renderWar(item);
		}
    }, this);
    this.count = wars.length;
    if (this.count == this.collection.length) {
      this.$("#load-more").hide();
    }

    return this;
  }
}
