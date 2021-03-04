import { BASE_ROOT } from "src/constants";
import BaseModel from "src/lib/BaseModel";
import _ from "underscore";

export interface INotification {
  id: number;
  message: string;
  link: string;
  read_at: string;
  created_at: string;
  notification_type?: string;
  ancient?: boolean;
}

export default class Notification extends BaseModel<INotification> {
  url = () => `${BASE_ROOT}/notifications`;

  markAsRead() {
    this.save(
      {},
      {
        url: `${this.url()}/${this.get("id")}/mark_as_read`,
      }
    );
  }
}
