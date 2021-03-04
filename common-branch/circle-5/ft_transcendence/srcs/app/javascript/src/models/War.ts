import Backbone from "backbone";
import _ from "underscore";
import Guild from "src/models/Guild";
import WarTime from "src/models/WarTime";
import { syncWithFormData } from "src/utils";
import BaseModel from "src/lib/BaseModel";
import Guilds from "src/collections/Guilds";
import WarTimes from "src/collections/WarTimes";
import { BASE_ROOT } from "src/constants";

export interface WarTimeDates {
	id: number;
	start: Date;
	end: Date;
  }

interface IWar {
  id: string;
  start: Date;
  end: Date;
  status: string;
  prize: string;
  time_to_answer: string;
  max_unanswered_calls: string;
  atWarTime: boolean;
  guilds: Guilds;
  warOpponent: Guild;
  warTimes: WarTimes;
  activeWarTime: WarTime;
  nb_games: number;
  nb_wartimes: number;
  winner: string;
  inc_ladder: boolean;
  inc_tour: boolean;
  inc_friendly: boolean;
  inc_easy: boolean;
  inc_normal: boolean;
  inc_hard: boolean;
  inc_three: boolean;
  inc_six: boolean;
  inc_nine: boolean;
  created_at: string;
  updated_at: string;
}

export type WAR_ACTION = "accept" | "reject";

export default class War extends BaseModel<IWar> {
  preinitialize() {
    this.relations = [
      {
        type: Backbone.Many,
        key: "guilds",
        collectionType: Guilds,
        relatedModel: Guild,
      },
      {
        type: Backbone.One,
        key: "warOpponent",
        relatedModel: Guild,
      },
      {
        type: Backbone.One,
        key: "activeWarTime",
        relatedModel: WarTime,
	  },
	  {
        type: Backbone.Many,
        key: "warTimes",
        collectionType: WarTimes,
        relatedModel: WarTime,
      },
    ];
  }

  constructor(options?: any) {
    super(options);
  }

  urlRoot = () => `${BASE_ROOT}/wars`;
  baseWarRoot = () => `${this.urlRoot()}/${this.get("id")}`;

  sync(method: string, model: War, options: JQueryAjaxSettings): any {
    return syncWithFormData(method, model, options);
  }

  createWar(
    start: Date,
    end: Date,
    prize: string,
    time_to_answer: string,
	max_unanswered_calls: string,
	inc_ladder: boolean,
	inc_tour: boolean,
	inc_friendly: boolean,
	inc_easy: boolean,
	inc_normal: boolean,
	inc_hard: boolean,
	inc_three: boolean,
	inc_six: boolean,
	inc_nine: boolean,
    initiator_id: string,
	recipient_id: string,
	wt_dates: WarTimeDates[],
  ) {
    return this.asyncSave(
      {
        start: start,
        end: end,
        prize: prize,
        time_to_answer: time_to_answer,
		max_unanswered_calls: max_unanswered_calls,
		inc_ladder: inc_ladder,
		inc_tour: inc_tour,
		inc_friendly: inc_friendly,
		inc_easy: inc_easy,
		inc_normal: inc_normal,
		inc_hard: inc_hard,
		inc_three: inc_three,
		inc_six: inc_six,
		inc_nine: inc_nine,
        initiator_id: initiator_id,
        recipient_id: recipient_id,
		wt_dates: JSON.stringify(wt_dates)
      },
      {
        url: this.urlRoot(),
      }
    );
  }

  modifyWar(
    start: Date,
    end: Date,
	prize: string,
    answer_time: string,
	max_calls: string,
	inc_ladder: boolean,
	inc_tour: boolean,
	inc_friendly: boolean,
	inc_easy: boolean,
	inc_normal: boolean,
	inc_hard: boolean,
	inc_three: boolean,
	inc_six: boolean,
	inc_nine: boolean,
	wt_dates: WarTimeDates[],
	wt_change: boolean,
  ) {
    return this.asyncSave(
      {
        start: start,
        end: end,
        prize: prize,
        time_to_answer: answer_time,
		max_unanswered_calls: max_calls,
		inc_ladder: inc_ladder,
		inc_tour: inc_tour,
		inc_friendly: inc_friendly,
		inc_easy: inc_easy,
		inc_normal: inc_normal,
		inc_hard: inc_hard,
		inc_three: inc_three,
		inc_six: inc_six,
		inc_nine: inc_nine,
		wt_dates: JSON.stringify(wt_dates),
		wt_change: wt_change,
      },
      {
        url: this.baseWarRoot(),
      }
    );
  }

  manageAction(method: WAR_ACTION) {
    return this.asyncSave(
      {},
      {
        url: `${this.baseWarRoot()}/${method}`,
      }
    );
  }

}
