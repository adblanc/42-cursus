import Backbone from "backbone";
import Mustache from "mustache";
import axios from "axios";
import { addAuthHeaders } from "../utils/auth";
import { displayError } from "../utils/toast";
import BaseView from "src/lib/BaseView";
import { BASE_ROOT } from "src/constants";

type Options = Backbone.ViewOptions & { user: string, tfa: string };

export default class TfaView extends BaseView {
	user: string;
	tfa: string;
	otp: string;

	constructor(options: Options) {
		super(options);
		
		this.user = options.user;
		this.tfa = options.tfa;
		this.otp = "";
	}

	events() {
		return { "keypress #input-tfa": "loginTfa" };
	}

	async loginTfa(e: JQuery.Event) {
		if (e.key === "Enter") {
			this.otp = <string>this.$("#input-tfa").val();
			e.preventDefault();
			if (!this.otp) { return ; }

			await axios.get(
				`${BASE_ROOT}/auth/tfa?user=${this.user}&tfa=${this.tfa}&otp=${this.otp}`
			).then((resp) => {
				addAuthHeaders(resp.data);
				Backbone.history.navigate("/", { trigger: true });
			}).catch((error) => {
				displayError(error.response.data.msg);
				if (error.response.data.typ == "att" || error.response.data.typ == "exp")
					Backbone.history.navigate("/auth", { trigger: true });
				else
					this.$("#input-tfa").val("");
			});
		}
	}

	render() {
		const template = $("#tfaTemplate").html();
		const html = Mustache.render(template, {});
		this.$el.html(html);
		return this;
	}
}
