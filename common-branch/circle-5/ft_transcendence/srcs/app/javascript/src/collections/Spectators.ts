import Backbone from "backbone";
import consumer from "channels/consumer";
import Spectator, { ISpectator } from "src/models/Spectator";

interface SpectatorData {
  action: "spectator_joined" | "spectator_left";
  payload: ISpectator;
}

export default class Spectators extends Backbone.Collection<Spectator> {
  spectatorsChannel: ActionCable.Channel = undefined;

  preinitialize() {
    this.model = Spectator;
  }

  connectToSpectatorsChannel(gameId: number) {
    this.unsubscribeSpectatorsChannel();
    this.spectatorsChannel = consumer.subscriptions.create(
      { channel: "GameSpectatorsChannel", id: gameId },
      {
        connected: () => {
        },
        received: ({ action, payload }: SpectatorData) => {
          if (
            action === "spectator_joined" &&
            !this.find((s) => s.get("id") === payload.id)
          ) {
            this.push(new Spectator(payload));
          } else if (action === "spectator_left") {
            const spectator = this.find((s) => s.get("id") === payload.id);

            if (spectator) {
              this.remove(spectator);
            }
          }
        },
      }
    );
  }

  unsubscribeSpectatorsChannel() {
    this.spectatorsChannel?.unsubscribe();
    this.spectatorsChannel = undefined;
  }
}
