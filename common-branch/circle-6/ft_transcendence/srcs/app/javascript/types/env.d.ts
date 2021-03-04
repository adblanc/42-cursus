declare namespace NodeJS {
  export interface ProcessEnv {
    NODE_ENV: "development" | "production" | "test";
    "42_ACCESS_TOKEN_URL": string;
    CLIENT_ID: string;
    CLIENT_SECRET: string;
    CLIENT_URL: string;
    CLIENT_REDIRECT: string;
    JWT_SECRET: string;
  }
}
