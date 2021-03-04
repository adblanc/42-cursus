import Backbone from "backbone";
import { BASE_ROOT } from "src/constants";
import BaseModel from "src/lib/BaseModel";
import { IProfile } from "./Profile";
import FriendRequests from "src/collections/FriendRequests";
import Friends from "src/collections/Friends";
import Game from "src/models/Game";
import Games from "src/collections/Games";
import Tournament from "./Tournament";
import Tournaments from "src/collections/Tournaments";
import { eventBus } from "src/events/EventBus";
import { AppearanceData, currentUser } from "./Profile/Profile";

export default class User extends BaseModel<IProfile> {
  urlRoot = () => `${BASE_ROOT}/profile/`;
  baseUserRoot = () => `${this.urlRoot()}/${this.get("id")}`;

  preinitialize() {
    this.relations = [
      {
        type: Backbone.Many,
        key: "friend_requests",
        collectionType: FriendRequests,
        relatedModel: User,
      },
      {
        type: Backbone.Many,
        key: "friends",
        collectionType: Friends,
        relatedModel: User,
      },
      {
        type: Backbone.Many,
        key: "games",
        collectionType: Games,
        relatedModel: Game,
      },
      {
        type: Backbone.Many,
        key: "won_tournaments",
        collectionType: Tournaments,
        relatedModel: Tournament,
      },
    ];
  }

  initialize() {
    this.listenTo(eventBus, "appeareance", this.reactToAppearance);
  }

  reactToAppearance({ event, user_id, appearing_on }: AppearanceData) {
    if (user_id === this.get("id")) {
      this.set({
        is_present: event === "appear",
        inGame: appearing_on === "in game",
        appearing_on,
      });
    }
  }

  isLadderChallengeable() {
    if (
      currentUser().get("pendingGame") ||
      currentUser().get("matchedGame") ||
      currentUser().get("currentGame") ||
      currentUser().get("id") === this.get("id") ||
      this.get("ladder_rank") >= currentUser().get("ladder_rank") ||
      this.justLostLadder()
    ) {
      return false;
    }

    return true;
  }

  justLostLadder() {
    if (this.get("id") == currentUser().get("ladder_unchallengeable")) {
      return true;
    }
    return false;
  }

  addFriend() {
    return this.asyncSave(
      {},
      {
        url: `${this.baseUserRoot()}/add_friend`,
      }
    );
  }

  acceptFriend() {
    return this.asyncSave(
      {},
      {
        url: `${this.baseUserRoot()}/accept_friend`,
      }
    );
  }

  refuseFriend() {
    return this.asyncSave(
      {},
      {
        url: `${this.baseUserRoot()}/refuse_friend`,
      }
    );
  }

  removeFriend() {
    return this.asyncSave(
      {},
      {
        url: `${this.baseUserRoot()}/remove_friend`,
      }
    );
  }
}
