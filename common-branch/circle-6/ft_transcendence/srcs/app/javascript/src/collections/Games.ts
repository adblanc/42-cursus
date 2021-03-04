import Backbone from "backbone";
import Game, { IGame } from "src/models/Game";
import { BASE_ROOT } from "src/constants";

export default class Games extends Backbone.Collection<Game> {
  constructor() {
    super();
    this.model = Game;
    this.url = `${BASE_ROOT}/games`;
  }

  fetchSpectateGames() {
    return this.fetch({
      url: `${this.url}/to_spectate`,
      success: () => {
        this.forEach((g) => g.connectToSpectatorsChannel());
      },
    });
  }

  addSpectateGame(game: IGame) {
    const newGame = this.push(new Game(game));

    newGame.connectToSpectatorsChannel();
  }

  removeSpectateGame(id: number) {
    const removed = this.remove(id.toString());

    removed?.unsubscribeSpectatorsChannel();
  }

  unsubSpectateGames() {
    this.forEach((g) => g.unsubscribeSpectatorsChannel());
  }
}
