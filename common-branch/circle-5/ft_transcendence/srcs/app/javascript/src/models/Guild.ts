import Backbone from "backbone";
import _ from "underscore";
import Profile from "src/models/Profile";
import Profiles from "src/collections/Profiles";
import War from "src/models/War";
import Wars from "src/collections/Wars";
import { syncWithFormData } from "src/utils";
import BaseModel from "src/lib/BaseModel";
import { BASE_ROOT } from "src/constants";

interface IGuild {
  id: string;
  name: string;
  ang: string;
  points: number;
  atWar?: "true" | "false";
  pendingWar?: "true" | "false";
  warInitiator?: "true" | "false";
  img_url?: string;
  members: Profiles;
  pending_members: Profiles;
  wars: Wars;
  activeWar: War;
  waitingWar: War;
  pendingWars: Wars;
  warOpponent: Guild;
  warPoints: string;
  created_at: string;
  updated_at: string;
  isOwner?: boolean;
  isInGuild?: boolean;
}

type CreatableGuildArgs = Partial<Pick<IGuild, "name" | "ang" | "img_url">>;

export type GUILD_ACTION = "promote" | "demote" | "fire" | "transfer";

export default class Guild extends BaseModel<IGuild> {
  preinitialize() {
    this.relations = [
      {
        type: Backbone.Many,
        key: "members",
        collectionType: Profiles,
        relatedModel: Profile,
      },
      {
        type: Backbone.Many,
        key: "pending_members",
        collectionType: Profiles,
        relatedModel: Profile,
      },
      {
        type: Backbone.Many,
        key: "wars",
        collectionType: Wars,
        relatedModel: War,
      },
      {
        type: Backbone.Many,
        key: "pendingWars",
        collectionType: Wars,
        relatedModel: War,
      },
      {
        type: Backbone.One,
        key: "activeWar",
        relatedModel: War,
      },
      {
        type: Backbone.One,
        key: "waitingWar",
        relatedModel: War,
      },
      {
        type: Backbone.One,
        key: "warOpponent",
        relatedModel: Guild,
      },
    ];
  }

  constructor(options?: any) {
    super(options);
  }

  defaults() {
    return {
      name: "",
      ang: "",
      points: 0,
      atWar: false,
      warInitiator: false,
      warPending: false,
      members: [],
      wars: [],
      pendingWars: [],
      activeWar: null,
      waitingWar: null,
      warOpponent: null,
    };
  }

  urlRoot = () => `${BASE_ROOT}/guilds`;
  baseGuildRoot = () => `${this.urlRoot()}/${this.get("id")}`;

  pointsPercentage = (maxPoints: number) => {
    return (this.get("points") / maxPoints) * 100;
  };

  get maxMemberPoints() {
    return this.get("members").isEmpty()
      ? 0
      : this.get("members")
          .max((m) => m.get("contribution"))
          .get("contribution");
  }

  sync(method: string, model: Guild, options: JQueryAjaxSettings): any {
    return syncWithFormData(method, model, options);
  }

  createGuild(attrs: CreatableGuildArgs) {
    return this.asyncSave(attrs, { url: this.urlRoot() });
  }

  modifyGuild(attrs: CreatableGuildArgs) {
    return this.asyncSave(attrs, {
      url: this.baseGuildRoot(),
    });
  }

  quit() {
    return this.asyncSave(
      {},
      {
        url: `${this.baseGuildRoot()}/quit`,
      }
    );
  }

  manageMembers(method: GUILD_ACTION, user_id: number) {
    return this.asyncSave(
      {
        user_id: user_id,
      },
      {
        url: `${this.baseGuildRoot()}/${method}`,
      }
    );
  }

  join() {
    return this.asyncSave(
      {},
      {
        url: `${this.baseGuildRoot()}/join`,
      }
    );
  }

  accept(user_id: number) {
    return this.asyncSave(
      { user_id: user_id },
      {
        url: `${this.baseGuildRoot()}/accept`,
      }
    );
  }

  reject(user_id: number) {
    return this.asyncSave(
      {
        user_id: user_id,
      },
      {
        url: `${this.baseGuildRoot()}/reject`,
      }
    );
  }

  withdraw() {
    return this.asyncSave(
      {},
      {
        url: `${this.baseGuildRoot()}/withdraw`,
      }
    );
  }
}
