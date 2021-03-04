import Mustache from "mustache";
import Backbone from "backbone";
import Game, { IGame } from "src/models/Game";
import BaseView from "src/lib/BaseView";
import CreateGameView from "./CreateGameView";
import CreateLadderGameView from "./CreateLadderGameView";
import { currentUser } from "src/models/Profile";
import { eventBus } from "src/events/EventBus";

type Options = Backbone.ViewOptions & { disable: boolean };

export default class StartGameView extends BaseView {
  disable: boolean;

  constructor(options?: Options) {
    super(options);

    this.disable = options.disable;

    this.listenTo(eventBus, "chatplay:change", this.relaunch);
    this.listenTo(currentUser(), "change", this.render);
  }

  relaunch() {
    currentUser().fetch({
      success: () => {
        if (currentUser().get("pendingGame")) {
          if (currentUser().get("pendingGame").get("game_type") == "chat")
            this.disable = true;
          else this.disable = false;
        } else {
          this.disable = false;
        }
        this.render();
      },
    });
  }

  events() {
    return {
      "click #friendly-btn": () => this.startGame("friendly"),
      "click #ladder-btn": () => this.startLadderGame(),
    };
  }

  startGame(type: IGame["game_type"]) {
    const game = new Game();
    const createGameView = new CreateGameView({
      model: game,
      type: type,
    });

    createGameView.render();
  }

  startLadderGame() {
    const createLadderGameView = new CreateLadderGameView();
    createLadderGameView.render();
  }

  render() {
    const template = $("#gameStartTemplate").html();
    const html = Mustache.render(template, {});
	this.$el.html(html);
	
	if (currentUser().get("pendingGameToAccept"))
	{
		this.$("#friendly-btn").addClass("btn-disabled");
		this.$("#ladder-btn").addClass("btn-disabled");
		this.$("#ladder-must-play").show();
	}
	if (currentUser().get("tournamentToPlay")) {
		this.$("#friendly-btn").addClass("btn-disabled");
		this.$("#ladder-btn").addClass("btn-disabled");
		this.$("#tour-must-play").show();
	}
	else if (this.disable == true) {
		this.$("#friendly-btn").addClass("btn-disabled");
		this.$("#ladder-btn").addClass("btn-disabled");
		this.$("#chat-game").show();
	}
    return this;
  }
}
