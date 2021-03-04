import { BASE_ROOT } from "src/constants";
import BaseModel from "src/lib/BaseModel";
import { IProfile } from "./Profile";
import Room from "./Room";

interface IRoomUser extends IProfile {
  roomRole: "Owner" | "Administrator" | "Member" | "Former member";
  isRoomAdministrator?: boolean;
  isBlocked?: boolean;
  isBan?: boolean;
}

export type MuteBanTime = "10mn" | "30mn" | "1h" | "24h" | "indefinitely";

export default class RoomUser extends BaseModel<IRoomUser> {
  room = (this.collection as any)?.parents[0] as Room;

  updateRole(action: "promoted" | "demoted") {
    return this.asyncSave(
      {
        update_action: action,
      },
      {
        url: `${BASE_ROOT}/${this.room?.get("id")}/${this.get(
          "id"
        )}/update_role`,
      }
    );
  }

  canBePromote() {
    return (
      this.get("roomRole") === "Administrator" ||
      this.get("roomRole") === "Member"
    );
  }

  canBeDemote() {
    return this.get("roomRole") === "Administrator";
  }

  mute(room_id: number, time: MuteBanTime) {
    return this.asyncSave(
      {
        room_mute_time: time,
      },
      {
        url: `${BASE_ROOT}/mute/${room_id}`,
      }
    );
  }

  unMute(room_id: number) {
    return this.asyncSave(
      {},
      {
        url: `${BASE_ROOT}/unmute/${room_id}`,
      }
    );
  }

  ban(room_id: number, time: MuteBanTime) {
    return this.asyncSave(
      {
        room_ban_time: time,
      },
      {
        url: `${BASE_ROOT}/ban/${room_id}`,
      }
    );
  }

  unBan(room_id: number) {
    return this.asyncSave(
      {},
      {
        url: `${BASE_ROOT}/unban/${room_id}`,
      }
    );
  }
}
