import Rect from "./Rect";
import Vec from "./Vec";

export default class Ball extends Rect {
  vel: Vec;

  constructor() {
    super(10, 10);

    this.vel = new Vec();
  }

  toJSON() {
    return {
      pos: {
        x: this.pos.x,
        y: this.pos.y,
      },
      vel: {
        ...this.vel,
        len: this.vel.len,
      },
    };
  }

  setJSON({ pos, vel }: ReturnType<typeof Ball.prototype.toJSON>) {
    this.vel.x = vel.x;
    this.vel.y = vel.y;
    this.vel.len = vel.len;
    this.pos.x = pos.x;
    this.pos.y = pos.y;
  }
}
