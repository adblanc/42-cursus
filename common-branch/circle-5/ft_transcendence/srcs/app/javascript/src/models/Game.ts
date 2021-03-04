import Backbone from "backbone";
import _ from "underscore";
import { currentUser } from "src/models/Profile";
import BaseModel from "src/lib/BaseModel";
import { BASE_ROOT } from "src/constants";
import consumer from "channels/consumer";
import { displayError, displaySuccess } from "src/utils/toast";
import { eventBus } from "src/events/EventBus";
import WarTime from "./WarTime";
import Spectators from "src/collections/Spectators";
import Spectator from "./Spectator";
import Players from "src/lib/Pong/collections/Players";
import Player from "src/lib/Pong/models/Player";
import Tournament from "src/models/Tournament";

export interface IGame {
  id: number;
  level?: string;
  goal?: number;
  status?:
    | "pending"
    | "started"
    | "finished"
    | "forfeit"
    | "paused"
    | "matched"
    | "abandon";
  last_pause?: number;
  pause_duration?: number;
  game_type?: "ladder" | "war_time" | "chat" | "friendly" | "tournament";
  isSpectator?: boolean;
  isHost?: boolean;
  players?: Players;
  spectators?: Spectators;
  war_time?: WarTime;
  created_at?: string;
  updated_at?: string;
  isTraining?: boolean;
  tournament?: Tournament;
}

export interface GameData {
  payload: any;

  action:
    | "matched"
    | "started"
    | "expired"
    | "player_movement"
    | "player_score"
    | "player_ready"
    | "game_over"
    | "game_paused"
    | "game_continue"
    | "round_stop";
  playerId: number;
}

export interface MovementData extends GameData {
  posY: number;
}

type CreatableGameArgs = Partial<Pick<IGame, "goal" | "level" | "game_type">>;

type ConstructorArgs = Pick<IGame, "id" | "isTraining">;

export default class Game extends BaseModel<IGame> {
  channel: ActionCable.Channel;
  private _timerInterval: any;

  preinitialize() {
    this.relations = [
      {
        type: Backbone.Many,
        key: "players",
        collectionType: Players,
        relatedModel: Player,
      },
      {
        type: Backbone.Many,
        key: "spectators",
        collectionType: Spectators,
        relatedModel: Spectator,
      },
      {
        type: Backbone.One,
        key: "war_time",
        relatedModel: WarTime,
      },
      {
        type: Backbone.One,
        key: "tournament",
        relatedModel: Tournament,
      },
    ];
  }

  constructor(options?: ConstructorArgs) {
    super(options);
  }

  defaults() {
    return {
      players: [],
      spectators: [],
      level: "easy",
    };
  }

  urlRoot = () => `${BASE_ROOT}/games`;
  baseGameRoot = () => `${this.urlRoot()}/${this.get("id")}`;

  get spectatorsNbr() {
    return this.get("spectators").size();
  }

  get winner() {
    return this.get("players").find((p) => p.get("status") === "won");
  }

  get looser() {
    return this.get("players").find((p) => p.get("status") === "lose");
  }

  get paused() {
    return this.get("status") === "paused";
  }

  fetchAndConnect() {
    return super.fetch({
      success: () => {
        this.connectToWS();
        if (this.paused) {
          const startDate = new Date(this.get("last_pause"));
          const endDate = new Date();

          const seconds = (endDate.getTime() - startDate.getTime()) / 1000;

          this.set(
            {
              pause_duration: Math.max(
                this.get("pause_duration") - Math.ceil(seconds),
                0
              ),
            },
            { silent: true }
          );

          this.startPauseTimer();
        }
      },
      error: () => {
        Backbone.history.navigate("/not-found", { trigger: true });
      },
    });
  }

  connectToWS() {
    this.createChannelConsumer();
    this.connectToSpectatorsChannel();
    this.playersListenToScore();
  }

  connectToSpectatorsChannel() {
    this.get("spectators").connectToSpectatorsChannel(this.get("id"));
  }

  playersListenToScore() {
    this.get("players").forEach((p) => p.listenToPlayerScored());
  }

  disconnectFromWS() {
    this.unsubscribeChannelConsumer();
    this.unsubscribeSpectatorsChannel();
    this.playersStopListenToScore();
  }

  unsubscribeSpectatorsChannel() {
    this.get("spectators").unsubscribeSpectatorsChannel();
  }

  playersStopListenToScore() {
    this.get("players").forEach((p) => p.stopListeningPlayerScored());
  }

  createChannelConsumer() {
    this.unsubscribeChannelConsumer();
    const gameId = this.get("id");

    this.channel = consumer.subscriptions.create(
      { channel: "GamingChannel", id: gameId },
      {
        received: (data: GameData) => {
          switch (data.action) {
            case "matched":
              this.onGameMatched();
              break;
            case "started":
              this.onGameStarted();
              break;
            case "expired":
              this.onGameExpired();
              break;
            case "game_paused":
              this.onGamePaused(data);
              break;
            case "game_continue":
              this.onGameContinue();
              break;
            case "player_ready":
              this.onPlayerReady(data);
              break;
            case "player_movement":
              this.onPlayerMovement(data);
              break;
            case "player_score":
              this.onPlayerScore(data);
              break;
            case "game_over":
              this.onGameOver(data);
              break;
            case "round_stop":
              displayError(
                "Tournament round has ended and your match was stopped."
              );
              break;
          }
        },
      }
    );
  }

  unsubscribeChannelConsumer() {
    this.channel?.unsubscribe();
    this.channel = undefined;
  }

  onGameMatched() {
    if (this.get("game_type") === "chat") {
      eventBus.trigger("playchat:expired", this.get("id"));
    }
    this.navigateToGame();
  }

  navigateToGame() {
    currentUser().set({ pendingGame: null });
    currentUser().set({ matchedGame: this.get("id") });
    this.disconnectFromWS();
    Backbone.history.navigate(`/game/${this.get("id")}`, {
      trigger: true,
    });
  }

  onGameStarted() {
    this.set({ status: "started" });
    currentUser().set({ currentGame: this.get("id") });
    currentUser().set({ matchedGame: null });
    this.channel?.perform("game_started", {});
  }

  onGameExpired() {
    if (this.get("game_type") == "friendly") {
      displayError(
        "We were not able to find an opponent. Please try different game settings."
      );
    }

    currentUser().fetch();
    this.disconnectFromWS();
  }

  onGamePaused(data: GameData) {
    if (this.get("status") !== "paused") {
      this.set({ status: "paused", ...data.payload }, { silent: true });
      this.startPauseTimer();
    }
  }

  startPauseTimer() {
    clearInterval(this._timerInterval);
    this._timerInterval = setInterval(() => {
      if (this.get("pause_duration") <= 0) {
        return clearInterval(this._timerInterval);
      }
      this.set(
        { pause_duration: this.get("pause_duration") - 1 },
        { silent: true }
      );
    }, 1000);
  }

  onGameContinue() {
    clearInterval(this._timerInterval);
    this.set({ status: "started" }, { silent: true });
  }

  onPlayerReady(data: GameData) {
    const player = this.get("players").find(
      (p) => p.get("id") === data.playerId
    );
    player?.set({ status: "ready" });
  }

  onPlayerMovement(data: GameData) {
    if (data.playerId !== currentUser().get("id")) {
      eventBus.trigger("pong:player_movement", data);
    }
  }

  onPlayerScore(data: GameData) {
    eventBus.trigger(`pong:player_scored:${data.playerId}`);
    eventBus.trigger("pong:player_scored");
  }

  onGameOver(data: GameData) {
    const winner = this.get("players").find(
      (p) => p.get("id") === data.payload?.winner.id
    );
    const looser = this.get("players").find(
      (p) => p.get("id") === data.payload?.looser.id
    );

    winner?.set(data.payload?.winner as object, { silent: true });
    looser?.set(data.payload?.looser as object, { silent: true });

    clearInterval(this._timerInterval);
    this.set({ status: "finished" });
    this.disconnectFromWS();
    currentUser().fetch();
  }

  createFriendly(attrs: CreatableGameArgs) {
    return this.asyncSave(attrs, { url: `${this.urlRoot()}/create_friendly` });
  }

  cancelFriendly() {
    return this.asyncDestroy({
      url: `${this.urlRoot()}/${this.get("id")}/cancel_friendly`,
    });
  }

  challengeWT(
    level: string,
    goal: number,
    game_type: string,
    warTimeId: string
  ) {
    return this.asyncSave(
      {
        level: level,
        goal: goal,
        game_type: game_type,
        warTimeId: warTimeId,
      },
      {
        url: `${this.urlRoot()}/challengeWT`,
      }
    );
  }

  acceptChallengeWT() {
    return this.asyncSave(
      {},
      {
        url: `${this.baseGameRoot()}/acceptChallengeWT`,
      }
    );
  }

  playChat(level: string, goal: number, room_id: number) {
    return this.asyncSave(
      {
        level: level,
        goal: goal,
        room_id: room_id,
      },
      {
        url: `${this.urlRoot()}/playChat`,
      }
    );
  }

  acceptPlayChat() {
    return this.asyncSave(
      {},
      {
        url: `${this.baseGameRoot()}/acceptPlayChat`,
      }
    );
  }

  ladderChallenge(opponent_id: number) {
    return this.asyncSave(
      {
        opponent_id: opponent_id,
      },
      {
        url: `${this.urlRoot()}/ladderChallenge`,
      }
    );
  }

  acceptLadderChallenge() {
    return this.asyncSave(
      {},
      {
        url: `${this.baseGameRoot()}/acceptLadderChallenge`,
      }
    );
  }

  startTournamentGame() {
    return this.asyncSave(
      {},
      {
        url: `${this.baseGameRoot()}/startTournamentGame`,
      }
    );
  }

  ready() {
    return this.asyncSave(
      {},
      {
        url: `${this.urlRoot()}/ready/${currentUser().get("id")}`,
      }
    );
  }

  giveUp() {
    return this.asyncSave(
      {},
      {
        url: `${this.urlRoot()}/give_up/${currentUser().get("id")}`,
      }
    );
  }
}
