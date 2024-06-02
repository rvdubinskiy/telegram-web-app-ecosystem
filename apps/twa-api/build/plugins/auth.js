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
var auth_exports = {};
__export(auth_exports, {
  default: () => auth_default
});
module.exports = __toCommonJS(auth_exports);
var import_jwt = __toESM(require("@fastify/jwt"));
var import_crypto = require("crypto");
var import_fastify_plugin = __toESM(require("fastify-plugin"));
const localAuthPlugin = (app, opts, done) => {
  const path = opts.path ?? "/auth";
  if ((typeof process.env.JWT_SECRET !== "string" || typeof process.env.REFRESH_SECRET !== "string") && (!opts.accessJwt || !opts.refreshJwt)) {
    throw new Error("Must provide a JWT secret");
  }
  app.register(
    import_jwt.default,
    opts.accessJwt ?? {
      // Default JWT configs
      secret: process.env.JWT_SECRET,
      sign: {
        algorithm: "HS256",
        expiresIn: 3600
        // 1 day
      },
      namespace: "access",
      jwtVerify: "accessVerify",
      jwtSign: "accessSign"
    }
  );
  app.register(
    import_jwt.default,
    opts.refreshJwt ?? {
      // Default Refresh JWT configs
      secret: process.env.REFRESH_SECRET,
      sign: {
        algorithm: "HS256",
        expiresIn: 60 * 60 * 24 * 30,
        // 30 days
        jti: (0, import_crypto.randomUUID)()
      },
      namespace: "refresh",
      jwtVerify: "refreshVerify",
      jwtSign: "refreshSign",
      jwtDecode: "refreshDecode"
    }
  );
  app.decorate("authorize", authorize);
  app.post(`${path}/signup`, async (req, reply) => {
    try {
      const user = await opts.signUp(req.body);
      const accessToken = await reply.accessSign(user, {
        sign: {
          sub: user.id
        }
      });
      const refreshToken = await reply.refreshSign(user, {
        sign: {
          sub: user.id
        }
      });
      return {
        accessToken,
        refreshToken,
        userId: user.id
      };
    } catch (e) {
      return reply.badRequest("Could not create user");
    }
  });
  app.post(`${path}/signin`, async (req, reply) => {
    try {
      const user = await opts.signin(req.body);
      if (!user) {
        return reply.notFound("User not found");
      }
      const accessToken = await reply.accessSign(user, {
        sign: {
          sub: user.id
        }
      });
      const refreshToken = await reply.refreshSign(user, {
        sign: {
          sub: user.id
        }
      });
      return {
        accessToken,
        refreshToken,
        userId: user.id,
        provider: "email"
      };
    } catch (e) {
      req.log.error(e);
      return reply.unauthorized("Request unauthorized.");
    }
  });
  app.post(`${path}/refresh`, async (req, reply) => {
    const { decoded, accessToken, refreshToken, message } = await refresh(req, reply);
    if (message || !accessToken) {
      return reply.unauthorized(message);
    }
    return {
      accessToken,
      refreshToken,
      userId: decoded.id,
      provider: decoded.provider
    };
  });
  async function authorize(req, reply) {
    if (!req.headers.authorization || req.headers.authorization.split(" ")[0] !== "Bearer") {
      return reply.unauthorized("Must include a Bearer authorization.");
    }
    try {
      await req.accessVerify();
    } catch (e) {
      req.log.error(e);
      if (opts.autoRefresh) {
        const { message } = await refresh(req, reply, true);
        if (message) {
          return reply.unauthorized(message);
        }
      } else {
        return reply.unauthorized("Invalid access token");
      }
    }
  }
  async function refresh(req, reply, includeHeader = false) {
    const { payload: decoded } = await req.refreshVerify({
      complete: true
    });
    if (!await opts.refresh(decoded.jti)) {
      return {
        decoded,
        accessToken: null,
        refreshToken: null,
        message: "Unauthorized request"
      };
    }
    const accessToken = await reply.accessSign(
      { id: decoded.id, provider: decoded.provider },
      {
        sign: {
          sub: decoded.id
        }
      }
    );
    const refreshToken = await reply.refreshSign(
      { id: decoded.id, provider: decoded.provider },
      {
        sign: {
          sub: decoded.id
        }
      }
    );
    return {
      decoded,
      accessToken,
      refreshToken,
      message: void 0
    };
  }
  done();
};
var auth_default = (0, import_fastify_plugin.default)(localAuthPlugin, { name: "localAuth" });
