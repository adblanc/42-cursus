import consumer from "channels/consumer";
import Mustache from "mustache";
import Games from "src/collections/Games";
import BaseView from "src/lib/BaseView";
import Game, { IGame } from "src/models/Game";
import GameToSpectateView from "./GameToSpectateView";

interface NewGameData {
  event: "new_game";

  game: IGame;
}

interface GameFinishedData {
  event: "finished_game";

  gameId: number;
}

type GameToSpectateData = NewGameData | GameFinishedData;

export default class GamesToSpectateView extends BaseView {
  games: Games;
  channel: ActionCable.Channel;

  constructor() {
    super();

    this.games = new Games();
    this.games.fetchSpectateGames();

    this.listenTo(this.games, "add", this.renderGameToSpectateView);
    this.listenTo(this.games, "remove", this.removeGameToSpectateView);
    this.channel = this.createGamesToSpectateChannel();
  }

  onClose = () => {
    this.channel.unsubscribe();
    this.games.unsubSpectateGames();
  };

  createGamesToSpectateChannel() {
    return consumer.subscriptions.create(
      { channel: "GamesToSpectateChannel" },
      {
        received: (data: GameToSpectateData) => {
          if (data.event === "new_game") {
            this.games.addSpectateGame(data.game);
          } else if (data.event === "finished_game") {
            this.games.removeSpectateGame(data.gameId);
          }
        },
      }
    );
  }

  renderGameToSpectateView(game: Game) {
    this.appendNested(
      new GameToSpectateView({
        model: game,
        id: `game-to-spectate-${game.get("id")}`,
      }),
      "#games-to-spectate-list"
    );
    this.renderRightTitle();
  }

  removeGameToSpectateView(game: Game) {
    this.$(`#game-to-spectate-${game.get("id")}`).remove();
    this.renderRightTitle();
  }

  renderRightTitle() {
    if (this.games.isEmpty()) {
      this.$("#games-title").hide();
    } else {
      this.$("#games-title").show();
    }
  }

  render() {
    const template = $("#games-to-spectate-template").html();

    const html = Mustache.render(template, {});

    this.$el.html(html);
    this.renderRightTitle();
    return this;
  }
}
