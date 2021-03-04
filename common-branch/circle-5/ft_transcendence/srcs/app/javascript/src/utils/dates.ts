import moment from "moment";

export const formatMessageDate = (date: string) => {
  const isToday =
    moment(date).format("DD/MM/YYYY") === moment().format("DD/MM/YYYY");

  return {
    time: moment(date).format("LT"),
    day: isToday ? "" : moment(date).format("DD/MM/YY"),
  };
};
