import Messages from "src/collections/Messages";
import RoomUsers from "src/collections/RoomUsers";
import { BASE_ROOT } from "src/constants";
import BaseModel from "src/lib/BaseModel";

export interface IRoom {
  name: string;
  password?: string;
  isOwner?: boolean;
  isInAdminList?: boolean;
  is_private?: boolean;
  is_dm?: boolean;
  id?: number;
  selected?: boolean;
  users?: RoomUsers;
  messages?: Messages;
}

export default class BaseRoom extends BaseModel<IRoom> {
  join() {
    return this.asyncFetch({
      url: `${BASE_ROOT}/join-room`,
      data: {
        name: this.get("name"),
        password: this.get("password"),
        is_private: this.get("is_private") ? true : null,
      },
    });
  }
}
