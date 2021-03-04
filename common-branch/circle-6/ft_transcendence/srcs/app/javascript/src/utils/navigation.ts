import Backbone from "backbone";

export const navigate = (e: JQuery.ClickEvent) => {
  const href = {
    prop: $(e.currentTarget).prop("href"),
    attr: $(e.currentTarget).attr("href"),
  };

  const root =
    location.protocol + "//" + location.host + Backbone.history.options.root;

  if (href.prop && href.prop.slice(0, root.length) === root) {
    Backbone.history.navigate(href.attr || "", {
      trigger: true,
    });
    e.preventDefault();
  }
};

export const catchNavigation = () => {
  $(document).on("click", "a", navigate);
};
