import consumer from "channels/consumer";
import { eventBus } from "src/events/EventBus";
import Game from "src/models/Game";
import { getRandomFloat } from "src/utils";
import BaseModel from "../BaseModel";
import Ball from "./classes/Ball";
import Paddle from "./classes/Paddle";
import Rect from "./classes/Rect";
import Player from "./models/Player";

const CHARS = [
  "111101101101111",
  "010010010010010",
  "111001111100111",
  "111001111001111",
  "101101111001001",
  "111100111001111",
  "111100111101111",
  "111001001001001",
  "111101111101111",
  "111101111001111",
];

const CHAR_PIXEL = 10;

interface IDifficultyOptions {
  initialBallSpeedMin: number;
  initialBallSpeedMax: number;
  ballSpeedFactor: number;
  paddleSpeedAi: number;
  ballDetectionRange: number;
}

type BallMovementData = ReturnType<typeof Ball.prototype.toJSON>;

export type Difficulty = "easy" | "normal" | "hard";

const DIFFICULTIES: Record<Difficulty, IDifficultyOptions> = {
  easy: {
    initialBallSpeedMin: 300,
    initialBallSpeedMax: 400,
    ballSpeedFactor: 1.05,
    paddleSpeedAi: 250,
    ballDetectionRange: 5,
  },
  normal: {
    initialBallSpeedMin: 400,
    initialBallSpeedMax: 500,
    ballSpeedFactor: 1.1,
    paddleSpeedAi: 275,
    ballDetectionRange: 10,
  },
  hard: {
    initialBallSpeedMin: 500,
    initialBallSpeedMax: 600,
    ballSpeedFactor: 1.15,
    paddleSpeedAi: 600,
    ballDetectionRange: 15,
  },
} as const;

export default class Pong extends BaseModel {
  public canvas: HTMLCanvasElement;
  private ctx: CanvasRenderingContext2D;
  private ball: Ball;
  private chars: HTMLCanvasElement[];
  private game: Game;
  private ballMovementChannel: ActionCable.Channel;
  private _nbrSeparations = 20;
  private _nbrSeparationsWithHoles = this._nbrSeparations * 2;

  constructor(canvas: HTMLCanvasElement, game: Game) {
    super();
    this.listenTo(eventBus, "pong:player_scored", this.onPlayerScored);
    this.listenTo(eventBus, "visibility:change", this.onVisibilityChange);
    this.canvas = canvas;
    this.ctx = canvas.getContext("2d");
    this.game = game;
    this.createBallMovementChannel();

    this.ball = new Ball();

    this.reset();

    if (this.game.get("isTraining")) {
      this.game.get("players").push(new Player());
      this.game.get("players").push(new Player());
    }

    this.game.get("players").at(0).posX = 40;
    this.game.get("players").at(1).posX = this.canvas.width - 40;

    this.game
      .get("players")
      .forEach((player) => (player.posY = this.canvas.height / 2));

    let lastTime;

    const callback = (ms: number) => {
      if (this.game.paused && lastTime) {
        this.drawPause();
      } else if (lastTime) {
        this.update((ms - lastTime) / 1000);
      }
      lastTime = ms;
      requestAnimationFrame(callback);
    };

    callback(undefined);

    this.chars = CHARS.map((str) => {
      const canvas = document.createElement("canvas");

      canvas.height = CHAR_PIXEL * 5;
      canvas.width = CHAR_PIXEL * 3;
      const context = canvas.getContext("2d");

      context.fillStyle = "#fff";
      str.split("").forEach((fill, i) => {
        if (fill === "1") {
          context.fillRect(
            (i % 3) * CHAR_PIXEL,
            ((i / 3) | 0) * CHAR_PIXEL,
            CHAR_PIXEL,
            CHAR_PIXEL
          );
        }
      });
      return canvas;
    });
  }

  close() {
    this.stopListening(eventBus, "pong:player_scored", this.onPlayerScored);
    this.stopListening(eventBus, "visibility:change", this.onVisibilityChange);
    this.unsubscribeBallMovement();
    this.unbind();
  }

  onPlayerScored() {
    if (!this.game.get("isHost")) {
      this.reset();
    }
  }

  onVisibilityChange(hidden: boolean) {
    if (hidden) {
      this.game.channel?.perform("game_paused", {});
    } else if (this.game.paused) {
      this.game.channel?.perform("game_continue", {});
    }
  }

  private get AI() {
    return this.game.get("players").at(1).paddle;
  }

  private get difficulty() {
    return DIFFICULTIES[this.game.get("level")];
  }

  createBallMovementChannel() {
    const id = this.game.get("id");

    this.ballMovementChannel = consumer.subscriptions.create(
      { channel: "PongBallChannel", id },
      {
        received: (data: BallMovementData) => {
          if (!this.game.get("isHost")) {
            if (!this.game.get("isSpectator")) {
              data.pos.x = this.canvas.width - data.pos.x;
            }
            this.ball.setJSON(data);
          }
        },
      }
    );
  }

  unsubscribeBallMovement() {
    this.ballMovementChannel?.unsubscribe();
  }

  drawPause() {
    this.ctx.fillStyle = "#000";
    this.ctx.fillRect(0, 0, this.canvas.width, this.canvas.height);

    this.ctx.font = "30px Arial";
    this.ctx.textAlign = "center";
    this.ctx.textBaseline = "middle";
    this.ctx.fillStyle = "#fff";
    this.ctx.fillText(
      "Waiting for player...",
      this.canvas.width / 2,
      this.canvas.height / 2
    );

    if (!this.game.get("isSpectator")) {
      this.ctx.fillText(
        `${this.game.get("pause_duration")}s before game's end`,
        this.canvas.width / 2,
        this.canvas.height / 2 + 45
      );
    }
  }

  update(dt: number) {
    if (this.game.get("isHost") || this.game.get("isTraining")) {
      this.ball.pos.x += this.ball.vel.x * dt;
      this.ball.pos.y += this.ball.vel.y * dt;
    }

    if (this.ball.left < 0 || this.ball.right > this.canvas.width) {
      const playerIndex = this.ball.vel.x < 0 ? 1 : 0;

      const player = this.game.get("players").at(playerIndex);

      player.score();
      this.reset();
    }

    if (this.ball.top < 0 || this.ball.bottom > this.canvas.height) {
      this.ball.vel.y = -this.ball.vel.y;
    }

    this.moveAI(dt);

    this.game
      .get("players")
      .forEach((player) => this.collide(player.paddle, this.ball));

    if (
      this.game.get("isHost") &&
      (this.ball.vel.x != 0 || this.ball.vel.y != 0)
    ) {
      this.ballMovementChannel.perform("movement", this.ball.toJSON());
    }

    this.draw();
  }

  reset() {
    this.ball.pos.x = this.canvas.width / 2;
    this.ball.pos.y = this.canvas.height / 2;
    this.ball.vel.x = 0;
    this.ball.vel.y = 0;
  }

  moveAI(dt: number) {
    if (!this.game.get("isTraining")) {
      return;
    }
    if (
      this.ball.pos.y - this.difficulty.ballDetectionRange > this.AI.top &&
      this.ball.pos.y < this.AI.bottom - this.difficulty.ballDetectionRange
    ) {
    } else if (this.ball.pos.y > this.AI.pos.y) {
      this.AI.pos.y += this.difficulty.paddleSpeedAi * dt;
    } else if (this.ball.pos.y < this.AI.pos.y) {
      this.AI.pos.y -= this.difficulty.paddleSpeedAi * dt;
    }
  }

  start() {
    if (!this.game.get("isHost") && !this.game.get("isTraining")) {
      return;
    }
    if (this.ball.vel.x === 0 && this.ball.vel.y === 0) {
      this.ball.vel.x = getRandomFloat(
        this.difficulty.initialBallSpeedMin,
        this.difficulty.initialBallSpeedMax
      );
      this.ball.vel.y = 0;
      this.ball.vel.y =
        getRandomFloat(
          this.difficulty.initialBallSpeedMin,
          this.difficulty.initialBallSpeedMax
        ) * (getRandomFloat(0, 1) > 0.5 ? 1 : -1);
      this.ball.vel.len = 200;
    }
  }

  collide(paddle: Paddle, ball: Ball) {
    if (
      paddle.left < ball.right &&
      paddle.right > ball.left &&
      paddle.top < ball.bottom &&
      paddle.bottom > ball.top
    ) {
      const len = ball.vel.len;
      ball.vel.x = -ball.vel.x;

      ball.vel.y += 25 * (Math.random() - 0.5);
      ball.vel.len = len * this.difficulty.ballSpeedFactor;
    }
  }

  draw() {
    this.ctx.fillStyle = "#000";
    this.ctx.fillRect(0, 0, this.canvas.width, this.canvas.height);

    this.drawRect(this.ball);
    this.game.get("players").forEach((player) => this.drawRect(player.paddle));

    this.drawScore();
    this.drawSeparation();
  }

  drawRect(rect: Rect) {
    this.ctx.fillStyle = "#fff";
    this.ctx.fillRect(rect.left, rect.top, rect.size.x, rect.size.y);
  }

  drawScore() {
    const align = this.canvas.width / 3;
    const CHAR_WIDTH = CHAR_PIXEL * 4;
    this.game.get("players").forEach((player, i) => {
      const chars = player.get("points").toString().split("");
      const offset =
        align * (i + 1) - (CHAR_WIDTH * chars.length) / 2 + CHAR_PIXEL / 2;

      chars.forEach((char, pos) => {
        this.ctx.drawImage(
          this.chars[(char as unknown) as number | 0],
          offset + pos * CHAR_WIDTH,
          20
        );
      });
    });
  }

  drawSeparation() {
    const height = this.canvas.height / this._nbrSeparations;

    this.ctx.strokeStyle = "white";

    for (let i = 0; i < this._nbrSeparationsWithHoles; i++) {
      if (i % 2) {
        continue;
      }
      this.ctx.beginPath();

      const beginY = i * height + height / 2;

      this.ctx.moveTo(this.canvas.width / 2, beginY);
      this.ctx.lineTo(this.canvas.width / 2, beginY + height);
      this.ctx.stroke();
    }
  }
}
