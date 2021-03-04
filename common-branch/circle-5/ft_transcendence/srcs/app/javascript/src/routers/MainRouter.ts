import Backbone from "backbone";
import axios from "axios";
import { pagesHandler } from "../lib/ViewsHandler";
import IndexView from "../views/IndexView";
import NotifPageView from "../views/NotifPageView";
import GuildView from "../views/guild/GuildView";
import GuildIndexView from "../views/guild/GuildIndexView";
import WarHistoryView from "../views/guild/WarHistoryView";
import NotFoundView from "../views/NotFoundView";
import GameView from "../views/game/GameView";
import GameIndexView from "../views/game/GameIndexView";
import TournamentIndexView from "../views/tournament/TournamentIndexView";
import LadderView from "../views/tournament/LadderView";
import TempTournamentView from "../views/tournament/TempTournamentView";
import { addAuthHeaders } from "../utils";
import AuthView from "../views/AuthView";
import TfaView from "../views/TfaView";
import Guild from "src/models/Guild";
import UserView from "../views/user/UserView";
import WarIndexView from "../views/wars/WarIndexView";
import { BASE_ROOT } from "src/constants";
import { displayError } from "../utils/toast";
import Tournament from "src/models/Tournament";
import TournamentView from "../views/tournament/TournamentView";
import HelpView from "../views/HelpView";

export default class MainRouter extends Backbone.Router {
  constructor() {
    super({
      routes: {
        "": "index",
        auth: "auth",
        "auth/callback?code=:code": "authCallBack",
        play: "play",
        "game/:id": "game",
        training: "training",
        guilds: "guilds",
        "guild/:id": "guild",
        "guild/:id/wars": "guildWarHistory",
        "me/notifications": "notifShow",
        "user/:id": "userShow",
        "tfa/:user/:tfa": "twoFactAuth",
        wars: "warsIndex",
        tournaments: "tournamentIndex",
        "tournaments/ladder": "ladder",
        "tournaments/temporary": "tempTournament",
        "tournaments/:id": "tournamentShow",
        help: "help",
        "*path": "notFound",
      },
    });
  }

  async authCallBack(code: string) {
    try {
      const { data: rsp } = await axios.get(
        `${BASE_ROOT}/auth/42?code=${code}`
      );
      if (!rsp.token) {
        this.navigate(`/tfa/${rsp.user}/${rsp.tfa}`, { trigger: true });
        return;
      }
      addAuthHeaders(rsp.token);
      this.navigate("/", { trigger: true });
    } catch (ex) {
      const resp = ex.response.data;

      if (resp.msg == "banned_user") {
        displayError(`${resp.user} is banned for the moment`);
      } else {
        displayError(`Logging as ${resp.user} has failed`);
      }
      this.navigate("/auth", { trigger: true });
    }
  }

  twoFactAuth(user: string, tfa: string) {
    const tfaView = new TfaView({ user: user, tfa: tfa });

    pagesHandler.showPage(tfaView, false, false);
  }

  auth() {
    const authView = new AuthView({});

    pagesHandler.showPage(authView, false, false);
  }

  index() {
    const indexView = new IndexView({
      className: "flex flex-col",
    });

    pagesHandler.showPage(indexView);
  }

  play() {
    const gameIndexView = new GameIndexView({});

    pagesHandler.showPage(gameIndexView);

    gameIndexView.checkCurrentGame();
  }

  notFound() {
    const notFoundView = new NotFoundView({});

    pagesHandler.showPage(notFoundView);
  }

  guilds() {
    const guildIndexView = new GuildIndexView();

    pagesHandler.showPage(guildIndexView);
  }

  guild(id: string) {
    const guildView = new GuildView({ guild: new Guild({ id }) });
    pagesHandler.showPage(guildView);
  }

  guildWarHistory(id: string) {
    const warHistoryView = new WarHistoryView({ guild: new Guild({ id }) });
    pagesHandler.showPage(warHistoryView);
  }

  game(id: string) {
    const gameView = new GameView({ gameId: id });
    pagesHandler.showPage(gameView);
  }

  help() {
    const helpView = new HelpView({});
    pagesHandler.showPage(helpView);
  }

  training() {
    const gameView = new GameView({ isTraining: true, gameId: "0" });
    pagesHandler.showPage(gameView);
  }

  notifShow() {
    const notifPageView = new NotifPageView();
    pagesHandler.showPage(notifPageView);
  }

  userShow(id: number) {
    const userView = new UserView({ userId: id });
    pagesHandler.showPage(userView);
  }

  warsIndex() {
    const warIndexView = new WarIndexView();
    pagesHandler.showPage(warIndexView);
  }

  tournamentIndex() {
    const tournamentIndexView = new TournamentIndexView();
    pagesHandler.showPage(tournamentIndexView);
  }

  ladder() {
    const ladderView = new LadderView();
    pagesHandler.showPage(ladderView);
  }

  tempTournament() {
    const tempTournamentView = new TempTournamentView();
    pagesHandler.showPage(tempTournamentView);
  }

  tournamentShow(id: number) {
    const tournamentView = new TournamentView({
      tournament: new Tournament({ id }),
    });
    pagesHandler.showPage(tournamentView);
  }
}
