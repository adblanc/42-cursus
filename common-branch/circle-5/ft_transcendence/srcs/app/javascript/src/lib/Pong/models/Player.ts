import { eventBus } from "src/events/EventBus";
import BaseModel from "src/lib/BaseModel";
import Game from "src/models/Game";
import Paddle from "../classes/Paddle";

interface IPlayer {
  id: number;
  name: string;
  points: number;
  status?: "lose" | "won" | "ready" | "accepted";
}

export default class Player extends BaseModel<IPlayer> {
  private _paddle: Paddle;

  initialize() {
    this._paddle = new Paddle();
  }

  defaults() {
    return {
      points: 0,
    };
  }

  listenToPlayerScored() {
    this.stopListeningPlayerScored();
    this.listenTo(eventBus, this.playerScoredEvent(), this.onScored);
  }

  stopListeningPlayerScored() {
    this.stopListening(eventBus, this.playerScoredEvent(), this.onScored);
  }

  playerScoredEvent = () => `pong:player_scored:${this.get("id")}`;

  get paddle() {
    return this._paddle;
  }

  get posX() {
    return this._paddle.pos.x;
  }

  get posY() {
    return this._paddle.pos.y;
  }

  set posX(value: number) {
    this._paddle.pos.x = value;
  }

  set posY(value: number) {
    this._paddle.pos.y = value;
  }

  get ready() {
    return this.get("status") === "ready";
  }

  private get game(): Game {
	//@ts-ignore
    return this.collection.parents[0];
  }

  private get channel(): ActionCable.Channel {
	//@ts-ignore
    return this.game.channel;
  }

  score() {
    if (this.game.get("isHost") || this.game.get("isTraining")) {
      this.set({ points: this.get("points") + 1 }, { silent: true });

      if (this.game.get("isHost")) {
        this.channel?.perform("player_score", { playerId: this.get("id") });
      }
    }
  }

  onScored() {
    if (!this.game.get("isHost")) {
      this.set({ points: this.get("points") + 1 }, { silent: true });
    }
  }
}
