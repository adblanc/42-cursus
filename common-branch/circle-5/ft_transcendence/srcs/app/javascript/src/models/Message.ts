import { BASE_ROOT } from "src/constants";
import Backbone from "backbone";
import BaseModel from "src/lib/BaseModel";
import Game from "./Game";
import User from "./User";

export interface IMessage {
  content: string;
  room_id: number;
  is_notification?: boolean;
  sent?: boolean;
  id?: number;
  avatar_url?: string;
  user_id?: number;
  pseudo?: string;
  game_id?: number;
  game?: Game;
  created_at?: string;
  updated_at?: string;
  ancient?: boolean;
}

export default class Message extends BaseModel<IMessage> {
	preinitialize() {
		this.relations = [
		  {
			type: Backbone.One,
			key: "game",
			relatedModel: Game,
		  },
		];
	}

  	url = () => `${BASE_ROOT}/room_messages`;
}
