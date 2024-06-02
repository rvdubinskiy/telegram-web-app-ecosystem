var __create = Object.create;
var __defProp = Object.defineProperty;
var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
var __getOwnPropNames = Object.getOwnPropertyNames;
var __getProtoOf = Object.getPrototypeOf;
var __hasOwnProp = Object.prototype.hasOwnProperty;
var __copyProps = (to, from, except, desc) => {
  if (from && typeof from === "object" || typeof from === "function") {
    for (let key of __getOwnPropNames(from))
      if (!__hasOwnProp.call(to, key) && key !== except)
        __defProp(to, key, { get: () => from[key], enumerable: !(desc = __getOwnPropDesc(from, key)) || desc.enumerable });
  }
  return to;
};
var __toESM = (mod, isNodeMode, target) => (target = mod != null ? __create(__getProtoOf(mod)) : {}, __copyProps(
  // If the importer is in node compatibility mode or this is not an ESM
  // file that has been converted to a CommonJS file using a Babel-
  // compatible transform (i.e. "__esModule" has not been set), then set
  // "default" to the CommonJS "module.exports" for node compatibility.
  isNodeMode || !mod || !mod.__esModule ? __defProp(target, "default", { value: mod, enumerable: true }) : target,
  mod
));
var import_http_proxy = __toESM(require("@fastify/http-proxy"));
var import_fastify = __toESM(require("fastify"));
const port = process.env.PORT ? parseInt(process.env.PORT, 10) : 8080;
const apiHost = "http://localhost:3010";
const clientHost = "http://localhost:3000";
const app = (0, import_fastify.default)({ logger: { level: "trace" } });
app.register(import_http_proxy.default, {
  upstream: apiHost + "/healthcheck",
  prefix: "/healthcheck/api",
  http2: false
});
app.register(import_http_proxy.default, {
  upstream: apiHost + "/api/v1/auth/signin",
  prefix: "/api/v1/auth/signin",
  http2: false
});
app.register(import_http_proxy.default, {
  upstream: apiHost + "/api/v1/auth/refresh",
  prefix: "/api/v1/auth/refresh",
  http2: false
});
app.register(import_http_proxy.default, {
  upstream: clientHost + "/",
  prefix: "/",
  http2: false
});
app.listen({ port, host: "::" });
