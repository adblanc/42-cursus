import ChatView from "src/views/Chat/ChatView";
import NavbarView from "src/views/NavbarView";
import NotificationsView from "src/views/NotificationsView";
import BaseView from "./BaseView";

class PagesHandler {
  private currentPage?: BaseView;
  private navbarView?: BaseView;
  private chatView?: ChatView;
  notificationsView?: BaseView;

  constructor() {
    this.currentPage = undefined;
    this.navbarView = undefined;
    this.chatView = undefined;
    this.notificationsView = undefined;
  }

  addNavbar() {
    this.removeNavbar();
    this.navbarView = new NavbarView();

    $("body").prepend(this.navbarView.render().el);

    this.notificationsView = new NotificationsView({
      className: "invisible",
    });

    this.notificationsView.render();

    $("body").append(this.notificationsView.el);
  }

  removeNavbar() {
    if (this.navbarView) {
      this.navbarView.close();
      this.navbarView = undefined;
    }
    if (this.notificationsView) {
      this.notificationsView.close();
      this.notificationsView = undefined;
    }
  }

  isNavbarDislayed() {
    return !!this.navbarView;
  }

  showPage(page: BaseView, withNavbar = true, withChat = true) {
    if (this.currentPage) {
      this.currentPage.close();
    }

    if (withNavbar && !this.isNavbarDislayed()) {
      this.addNavbar();
    } else if (!withNavbar) {
      this.removeNavbar();
    }

    this.currentPage = page;
    this.currentPage.render();

    $("#container").html(this.currentPage.el);

    this.handleChat(withChat);
  }

  handleChat(withChat: boolean) {
    if (!withChat) {
      if (this.chatView) {
        return this.closeChat();
      }
      return;
    }

    if (!this.chatView) {
      this.chatView = new ChatView({
        className: "invisible",
      });

      $("body").append(this.chatView.render().el);
    } else {
      this.chatView.hideChat();
    }
  }

  closeChat() {
    this.chatView.close();
    this.chatView = undefined;
  }
}

export const pagesHandler = new PagesHandler();
