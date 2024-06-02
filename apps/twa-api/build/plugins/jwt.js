"use strict";
var __create = Object.create;
var __defProp = Object.defineProperty;
var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
var __getOwnPropNames = Object.getOwnPropertyNames;
var __getProtoOf = Object.getPrototypeOf;
var __hasOwnProp = Object.prototype.hasOwnProperty;
var __export = (target, all) => {
  for (var name in all)
    __defProp(target, name, { get: all[name], enumerable: true });
};
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
var __toCommonJS = (mod) => __copyProps(__defProp({}, "__esModule", { value: true }), mod);
var jwt_exports = {};
__export(jwt_exports, {
  default: () => jwt_default
});
module.exports = __toCommonJS(jwt_exports);
var import_jwt = __toESM(require("@fastify/jwt"));
var import_crypto = require("crypto");
var import_fastify_plugin = __toESM(require("fastify-plugin"));
var import_refresh = require("../helpers/refresh");
const publicRoutes = ["/healthcheck", "/v1/auth", "/v1/auth/refresh"];
const ACCESS_SECRET = "lopEjWIKZwHYNTqm+1ZmXvZCUyyvTUQcPUUt7ppP5y5nM7b54mykuhPEyrO3U3m+L71hXkaOMRcF28cJOIQBWmpCA8nN4DGVPkoPEQh1FQChWvSfRWxo3i3OJYxC2DfejlLuVOFBSEQyU0igQvbtHmKMCF9Dpzj6+v9DOnr6uK9YleePzvlKtFwEQsLbldfqGzEbhyoo1t0AsULfDQDkw6HBhQn3Uw7qIcXD458wwW4CdqIPv0SV81bLGhBtSs313jDVxY/YZ6DhjRkDeUmMdBEarwQ/h6feTvD+b5CeJ2ZAUe5kec+FcrunsK2e6mEertI4QhfVRuJKY1petRxhSQ==";
const REFRESH_SECRET = "lopEjWIKZwHYNTqm+1ZmXvZCUyyvTUQcPUUt7ppP5y5nM7b54mykuhPEyrO3U3m+L71hXkaOMRcF28cJOIQBWmpCA8nN4DGVPkoPEQh1FQChWvSfRWxo3i3OJYxC2DfejlLuVOFBSEQyU0igQvbtHmKMCF9Dpzj6+v9DOnr6uK9YleePzvlKtFwEQsLbldfqGzEbhyoo1t0AsULfDQDkw6HBhQn3Uw7qIcXD458wwW4CdqIPv0SV81bLGhBtSs313jDVxY/YZ6DhjRkDeUmMdBEarwQ/h6feTvD+b5CeJ2ZAUe5kec+FcrunsK2e6mEertI4QhfVRuJKY1petRxhSQ==";
const jwt = async (app) => {
  await app.register(import_jwt.default, {
    secret: ACCESS_SECRET,
    sign: {
      algorithm: "HS256",
      expiresIn: "10d"
    },
    namespace: "access",
    jwtVerify: "accessVerify",
    jwtSign: "accessSign"
  });
  await app.register(import_jwt.default, {
    secret: REFRESH_SECRET,
    sign: {
      algorithm: "HS256",
      expiresIn: "30d",
      jti: (0, import_crypto.randomUUID)()
    },
    namespace: "refresh",
    jwtVerify: "refreshVerify",
    jwtSign: "refreshSign",
    jwtDecode: "refreshDecode"
  });
  app.addHook("onRequest", async (req, reply) => {
    const route = req.url ?? "";
    if (publicRoutes.includes(route)) {
      return;
    }
    if (!req.headers.authorization || req.headers.authorization.split(" ")[0] !== "Bearer") {
      return reply.unauthorized("Must include a Bearer authorization.");
    }
    try {
      await req.accessVerify();
    } catch (e) {
      req.log.error(e);
      const { error, message } = await (0, import_refresh.refresh)(req, reply);
      if (error) {
        return reply.unauthorized(message);
      }
    }
  });
};
var jwt_default = (0, import_fastify_plugin.default)(jwt);
