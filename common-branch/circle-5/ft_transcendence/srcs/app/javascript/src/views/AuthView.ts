import Backbone from "backbone";
import Mustache from "mustache";
import axios from "axios";
import { get42LoginUrl } from "../utils/api";
import { addAuthHeaders } from "../utils/auth";
import { displayError } from "../utils/toast";
import BaseView from "src/lib/BaseView";
import { BASE_ROOT } from "src/constants";

export default class AuthView extends BaseView {
  events() {
    return {
      "keypress #input-guest": "loginGuest",
    };
  }

  async loginGuest(e: JQuery.Event) {
    if (e.key === "Enter") {
      const input = this.$("#input-guest").val();
      e.preventDefault();
      if (!input) {
        return;
      }
      try {
        const { data: rsp } = await axios.get(
          `${BASE_ROOT}/auth/guest?login=${input}`
        );
        if (!rsp.token) {
          Backbone.history.navigate(`/tfa/${rsp.user}/${rsp.tfa}`, {
            trigger: true,
          });
          return;
        }
        addAuthHeaders(rsp.token);
      } catch (ex) {
		if (ex.response.data.msg == "banned_user") {
			displayError(`${input} is banned for the moment`);
		} else {
			displayError(`${input} is an invalid guest`);
		}
        this.$("#input-guest").val("");
        return;
      }

      Backbone.history.navigate("/", { trigger: true });
    }
  }

  render() {
    const template = $("#loginTemplate").html();
    const html = Mustache.render(template, {
      "42_LOGIN_URL": get42LoginUrl(),
    });
    this.$el.html(html);
    return this;
  }
}
