import Backbone from "backbone";
import _ from "underscore";

export const eventBus = _.extend({}, Backbone.Events) as Backbone.Events;
