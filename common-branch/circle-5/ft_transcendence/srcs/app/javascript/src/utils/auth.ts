import Backbone from "backbone";
import { AUTH_TOKEN } from "src/constants";

const BackboneAjax = Backbone.ajax;

export const addAuthHeaders = (token: string) => {
  localStorage.setItem(AUTH_TOKEN, token);
  Backbone.ajax = function (options) {
    return BackboneAjax({
      ...options,
      headers: {
        Authorization: `Bearer ${token}`,
      },
    });
  };
};

export const clearAuthHeaders = () => {
  Backbone.ajax = BackboneAjax;
  localStorage.removeItem(AUTH_TOKEN);
};
