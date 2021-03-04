import Backbone from "backbone";
import Mustache from "mustache";
import { eventBus } from "src/events/EventBus";
import BaseView from "src/lib/BaseView";
import Pong from "src/lib/Pong";
import Game, { MovementData } from "src/models/Game";
import { currentUser } from "src/models/Profile";
import SpectatorsView from "./SpectatorsView";

type Options = Backbone.ViewOptions<Game> & {
  gameId: string;
  isTraining?: boolean;
};

export default class GameView extends BaseView<Game> {
  pong: Pong | undefined;
  spectatorsView: SpectatorsView;

  constructor(options: Options) {
    super(options);

    this.pong = undefined;
    this.model = new Game({
      id: parseInt(options.gameId),
      isTraining: options.isTraining,
    });
    this.spectatorsView = undefined;

    if (options.isTraining) {
      return;
    }

    this.spectatorsView = new SpectatorsView({
      spectators: this.model.get("spectators"),
    });

    this.model.fetchAndConnect();

    this.listenTo(eventBus, "pong:player_movement", this.moveOtherPlayer);
    this.listenTo(this.model, "change", this.render);
    this.listenTo(this.model.get("players"), "change", this.render);
  }

  events() {
    return {
      "mousemove #pong": this.onMouseMove,
      "click #pong": this.onClick,
      "click #btn-ready": this.onReady,
      "click #give-up": this.onGiveUp,
      "change input[name=level]": this.onDifficultyChange,
    };
  }

  onClose = () => {
    this.model.disconnectFromWS();
    this.pong?.unsubscribeBallMovement();
  };

  onReady() {
    this.model.ready();
  }

  onGiveUp() {
    this.model.giveUp();
  }

  onDifficultyChange(e: JQuery.ChangeEvent) {
    if (this.model.get("isTraining")) {
      this.model.set({ level: $(e.currentTarget).val() as string });
    }
  }

  moveOtherPlayer(data: MovementData) {
    let index = 1;

    if (this.model.get("isSpectator")) {
      index = this.model
        .get("players")
        .findIndex((u) => u.get("id") === data.playerId);
    }

    this.model.get("players").at(index).posY = data.posY;
  }

  onMouseMove(e: JQuery.MouseMoveEvent) {
    if (this.pong && !this.model?.get("isSpectator") && !this.model?.paused) {
      const scale = e.offsetY / e.target.getBoundingClientRect().height;

      this.model.get("players").at(0).posY = this.pong.canvas.height * scale;

      if (!this.model.get("isTraining")) {
        this.model.channel?.perform("player_movement", {
          playerId: currentUser().get("id"),
          posY: this.model.get("players").at(0).posY,
        });
      }
    }
  }

  onClick() {
    if (this.model.get("isHost") || this.model.get("isTraining")) {
      this.pong?.start();
    }
  }

  renderSpectators() {
    if (this.spectatorsView) {
      this.renderNested(this.spectatorsView, "#spectators");
    }
  }

  render() {
    if (!this.model.get("isTraining") && !this.model.get("status")) {
      return;
    }

    const isFinished =
      this.model.get("status") === "finished" ||
      this.model.get("status") === "forfeit";
    const isMatched = this.model.get("status") === "matched";

    if (isFinished) currentUser().set({ currentGame: null });

    const firstPlayer = this.model.get("players")?.first();
    const secondPlayer = this.model.get("players")?.last();

    const html = Mustache.render(this.template(), {
      ...this.model?.toJSON(),
      hostName: this.model.get("isHost")
        ? firstPlayer?.get("name")
        : secondPlayer?.get("name"),
      isTraining: this.model.get("isTraining"),
      firstPlayer: { ...firstPlayer?.toJSON(), isReady: firstPlayer?.ready },
      secondPlayer: { ...secondPlayer?.toJSON(), isReady: secondPlayer?.ready },
      winner: this.model.winner?.toJSON(),
      looser: this.model.looser?.toJSON(),
      isFinished,
      isMatched,
      isSpectator: this.model.get("isSpectator"),
      game_type: this.gameType(),
    });
    this.$el.html(html);

    if (isFinished || isMatched) {
      return this;
    }

    this.renderSpectators();

    this.renderPong();

    return this;
  }

  gameType() {
    switch (this.model.get("game_type")) {
      case "chat":
        return "Friendly";
      case "war_time":
        return "War time";
      case undefined:
        return "";
      default:
        return (
          this.model.get("game_type")[0].toUpperCase() +
          this.model.get("game_type").slice(1)
        );
    }
  }

  template() {
    return $("#playGameTemplate").html();
  }

  renderPong() {
    if (this.pong) {
      this.pong.close();
    }
    const canvas = this.$("#pong")[0] as HTMLCanvasElement;

    this.pong = new Pong(canvas, this.model);
  }
}
