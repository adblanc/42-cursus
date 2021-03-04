import Backbone from "backbone";
import "backbone-associations";
import { handleServerErrors, mapServerErrors } from "src/utils";

export default class BaseModel<
  T = any,
  S = Backbone.ModelSetOptions,
  E = {}
> extends Backbone.AssociatedModel<T, S, E> {
  asyncFetch(options?: Backbone.ModelFetchOptions): Promise<boolean> {
    return handleServerErrors(
      new Promise((res, rej) => {
        this.fetch({
          ...options,
          success: () => res(true),
          error: (_, jqxhr) => {
            rej(mapServerErrors(jqxhr.responseJSON));
          },
        });
      })
    );
  }

  asyncDestroy(options?: Backbone.ModelDestroyOptions): Promise<any> {
    return handleServerErrors(
      new Promise((res, rej) => {
        this.destroy({
          ...options,
          success: (_, rsp) => res(rsp || true),
          error: (_, jqxhr) => {
            rej(mapServerErrors(jqxhr.responseJSON));
          },
        });
      })
    );
  }

  asyncSave(
    attrs?: any,
    options?: Backbone.ModelSaveOptions
  ): Promise<boolean> {
    return handleServerErrors(
      new Promise((res, rej) => {
        const valid = this.save(attrs, {
          wait: true,
          ...options,
          success: () => res(true),
          error: (_, jqxhr) => {
            return rej(mapServerErrors(jqxhr.responseJSON));
          },
        });
        if (!valid) {
          rej([this.validationError]);
        }
      })
    );
  }
}
