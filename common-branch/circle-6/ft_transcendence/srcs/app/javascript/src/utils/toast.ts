import Toastify from "toastify-js";
import "toastify-js/src/toastify.css";

const ERROR_COLOR = "#FA113D";
const SUCCESS_COLOR = "#4BB543";

type ToastArgs = Parameters<typeof Toastify>[0];
type ToastType = "success" | "error";

export const displayToast = (args: ToastArgs, type: ToastType) => {
  Toastify({
    backgroundColor: type === "success" ? SUCCESS_COLOR : ERROR_COLOR,
    className: "mt-20",
    ...args,
  }).showToast();
};

export const displayError = (error: string) => {
  displayToast({ text: error }, "error");
};

export const displaySuccess = (text: string) => {
  displayToast({ text }, "success");
};
