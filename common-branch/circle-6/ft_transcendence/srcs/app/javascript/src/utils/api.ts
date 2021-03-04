export const get42LoginUrl = () => {
  const uri = `${process.env.CLIENT_URL}/auth/callback`;

  return `https://api.intra.42.fr/oauth/authorize?client_id=985e6a3c25c5abe47dc63177f9c789c27d1c138a856a1b1a57938ba5207c3b3d&redirect_uri=${uri}&response_type=code`;
};
