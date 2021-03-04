/**
 * @param {number} min (inclusive)
 * @param {number} max (exclusive)
 */
export const getRandomFloat = (min: number, max: number) => {
  return Math.random() * (max - min) + min;
};

export const closeAllModal = () => {
  $(".modal-backdrop").parent().off();
  $(".modal-backdrop").parent().remove();
};
