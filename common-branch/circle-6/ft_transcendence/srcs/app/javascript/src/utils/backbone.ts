import Backbone from "backbone";
import _ from "underscore";

export const syncWithFormData = (
  method: string,
  model: Backbone.Model,
  options: JQueryAjaxSettings
): any => {
  if (method == "create" || method == "update") {
    var formData = new FormData();

    _.each(model.attributes, function (value, key) {
      formData.append(key, value);
    });
    _.defaults(options || (options = {}), {
      data: formData,
      processData: false,
      contentType: false,
    });
  }
  return Backbone.sync.call(this, method, model, options);
};
