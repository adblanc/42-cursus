import Backbone from "backbone";
import _ from "underscore";
import War from "src/models/War";
import { mapServerErrors, syncWithFormData } from "src/utils";
import BaseModel from "src/lib/BaseModel";
import User from "./User";
import Guild from "./Guild";
import Game from "./Game";

interface IWarTime {
  id: string;
  start: Date;
  end: Date;
  time_to_answer: string;
  max_unanswered_calls: string;
  unanswered_calls: string;
  activeGame: Game;
  pendingGame: Game;
  pendingGameInitiator: User;
  pendingGameGuildInitiator: Guild;
  created_at: string;
  updated_at: string;
}

export default class WarTime extends BaseModel<IWarTime> {
	preinitialize() {
		this.relations = [
		  {
			type: Backbone.One,
			key: "war",
			relatedModel: War,
		  },
		  {
			type: Backbone.One,
			key: "activeGame",
			relatedModel: Game,
		  },
		  {
			type: Backbone.One,
			key: "pendingGame",
			relatedModel: Game,
		  },
		  {
			type: Backbone.One,
			key: "pendingGameInitiator",
			relatedModel: User,
		  },
		  {
			type: Backbone.One,
			key: "pendingGameGuildInitiator",
			relatedModel: Guild,
		  },
		];
	  }

  constructor(options?: any) {
    super(options);
  }
}


