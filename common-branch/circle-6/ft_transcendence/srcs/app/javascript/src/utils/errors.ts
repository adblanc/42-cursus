import { displayError } from "./toast";

export const mapServerErrors = (errors: Record<string, string[]>) => {
  if (!errors) {
    return [""];
  }
  return Object.keys(errors).map((key) => `${key} ${errors[key].join(",")}`);
};

export const displayErrors = (error: string[]) => {
  error.forEach((err) => displayError(err));
};

export const handleServerErrors = async (
  promise: Promise<any>
): Promise<any | null> => {
  try {
    const res = await promise;

    return res;
  } catch (errors) {
    if (typeof errors === "object" && Array.isArray(errors)) {
      displayErrors(errors);
    }

    return null;
  }
};
