import Backbone from "backbone";

interface ITab {
  name: string;
  id: number;
}

export default class Tab extends Backbone.Model<ITab> {}
