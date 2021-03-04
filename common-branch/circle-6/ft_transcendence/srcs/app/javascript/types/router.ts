export type RouterOptions<T> = Omit<Backbone.RouterOptions, "routes"> & {
    routes: Record<string, keyof T>;
};
