import Mustache from "mustache";
import MyRooms from "src/collections/MyRooms";
import { eventBus } from "src/events/EventBus";
import BaseView from "src/lib/BaseView";
import ChatHeaderView from "./Header/ChatHeaderView";
import ChatInputView from "./ChatInputView";
import CreateJoinChannelView from "./CreateJoinChannelView";
import PublicRoomsView from "./PublicRoomsView";
import MyRoomsView from "./MyRoomsView";
import DirectMessagesView from "./DirectMessagesView";
import Room from "src/models/Room";
import AdminRoomsView from "./AdminRoomsView";
import { currentUser } from "src/models/Profile";

export default class ChatView extends BaseView {
  myRooms: MyRooms;
  publicRoomsView: PublicRoomsView;
  myRoomsView: MyRoomsView;
  adminRoomsView: AdminRoomsView;
  directMessagesView: DirectMessagesView;
  createJoinChannelView: CreateJoinChannelView;
  chatHeaderView?: ChatHeaderView;
  chatInputView?: ChatInputView;

  constructor(options?: Backbone.ViewOptions) {
    super(options);

    this.myRooms = new MyRooms();
    this.myRooms.fetch();

    this.myRoomsView = new MyRoomsView({
      myRooms: this.myRooms,
    });

    this.directMessagesView = new DirectMessagesView({
      myRooms: this.myRooms,
    });

    this.adminRoomsView = new AdminRoomsView({
      myRooms: this.myRooms,
    });

    this.createJoinChannelView = new CreateJoinChannelView({
      rooms: this.myRooms,
    });

    this.publicRoomsView = new PublicRoomsView();

    this.chatHeaderView = undefined;
    this.chatInputView = undefined;

    this.listenTo(eventBus, "chat:toggle", this.toggleChat);
    this.listenTo(eventBus, "chat:close", this.hideChat);
    this.listenTo(eventBus, "chat:open", this.showChat);
    this.listenTo(eventBus, "chat:go-to-dm", this.goToDm);
    this.listenTo(this.myRooms, "remove", this.removeHeaderInput);
    this.listenTo(eventBus, "chat:room-selected", this.onRoomSelected);
    this.listenTo(currentUser(), "change:admin", this.renderAdminRoomList);
  }

  onClose = () => {
    this.myRoomsView.close();
    this.adminRoomsView.close();
    this.directMessagesView.close();
    this.createJoinChannelView.close();
    this.publicRoomsView.close();
    this.chatHeaderView?.close();
    this.chatInputView?.close();
  };

  onRoomSelected() {
    this.refreshHeaderInput();
  }

  private isVisible() {
    return !this.$el.hasClass("invisible");
  }

  hideChat() {
    if (!this.isVisible()) {
      return;
    }
    this.toggleChat();
  }

  showChat() {
    if (this.isVisible()) {
      return;
    }
    this.toggleChat();
  }

  toggleChat() {
    this.$el.toggleClass("invisible");
  }

  refreshHeaderInput() {
    if (!this.chatHeaderView) {
      this.chatHeaderView = new ChatHeaderView({
        rooms: this.myRooms,
      });
      this.renderChatHeader();
    }
    if (!this.chatInputView) {
      this.chatInputView = new ChatInputView({
        rooms: this.myRooms,
      });
      this.renderChatInput();
    }
  }

  removeHeaderInput() {
    if (!this.myRoomsLength() && !this.adminRoomsLength()) {
      if (this.chatHeaderView) {
        this.chatHeaderView.close();
        this.chatHeaderView = undefined;
      }
      if (this.chatInputView) {
        this.chatInputView.close();
        this.chatInputView = undefined;
      }

      this.$("#messages-container").empty();
    }
  }

  myRoomsLength = () => this.$("#my-rooms-list").children().length;
  adminRoomsLength = () => this.$("#admin-rooms-list").children().length;

  async goToDm(userId: number) {
    const dmRoom = this.myRooms.find(
      (r) =>
        r.get("is_dm") && !!r.get("users").find((u) => u.get("id") === userId)
    );

    if (dmRoom) {
      if (!dmRoom.get("selected")) {
        dmRoom.select();
      }
    } else {
      const dmRoom = new Room();
      const success = await dmRoom.createDm(userId);

      if (success) {
        this.myRooms.add(dmRoom);
        dmRoom.select();
      }
    }
  }

  render() {
    const template = $("#chat-container-template").html();
    const html = Mustache.render(template, {});
    this.$el.html(html);

    this.preprendNested(this.createJoinChannelView, "#left-container-chat");

    this.appendNested(this.directMessagesView, "#left-container-chat");
    this.appendNested(this.myRoomsView, "#left-container-chat");
    this.appendNested(this.publicRoomsView, "#left-container-chat");

    this.renderAdminRoomList();

    return this;
  }

  renderAdminRoomList() {
    if (currentUser().get("admin")) {
      this.appendNested(this.adminRoomsView, "#left-container-chat");
    }
  }

  renderChatHeader() {
    this.preprendNested(this.chatHeaderView, "#right-container-chat");
  }

  renderChatInput() {
    this.appendNested(this.chatInputView, "#right-container-chat");
  }
}
