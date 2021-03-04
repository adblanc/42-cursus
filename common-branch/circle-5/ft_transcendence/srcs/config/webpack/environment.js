const { environment } = require("@rails/webpacker");
const webpack = require("webpack");
const typescript = require("./loaders/typescript");
const dotenv = require("dotenv");

const dotEnvFiles = [
  ".env"
];

dotEnvFiles.forEach(file => {
  dotenv.config({path: file, silent: true})
});

environment.plugins.insert(
  "Environment",
  new webpack.EnvironmentPlugin(process.env)
)

environment.plugins.append(
  "Provide",
  new webpack.ProvidePlugin({
    $: "jquery",
    jQuery: "jquery",
  })
);

environment.loaders.prepend("typescript", typescript);
module.exports = environment;