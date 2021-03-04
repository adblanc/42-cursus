import Backbone from "backbone";
import Message from "../models/Message";

export default class Messages extends Backbone.Collection<Message> {
  constructor() {
    super();

    this.model = Message;
  }
}
