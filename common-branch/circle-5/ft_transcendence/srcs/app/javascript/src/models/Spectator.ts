import BaseModel from "src/lib/BaseModel";

export interface ISpectator {
  id: number;
  name: string;
}

export default class Spectator extends BaseModel<ISpectator> {}
