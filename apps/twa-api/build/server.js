'use strict';
var __create = Object.create;
var __defProp = Object.defineProperty;
var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
var __getOwnPropNames = Object.getOwnPropertyNames;
var __getProtoOf = Object.getPrototypeOf;
var __hasOwnProp = Object.prototype.hasOwnProperty;
var __copyProps = (to, from, except, desc) => {
  if ((from && typeof from === 'object') || typeof from === 'function') {
    for (let key of __getOwnPropNames(from))
      if (!__hasOwnProp.call(to, key) && key !== except)
        __defProp(to, key, {
          get: () => from[key],
          enumerable: !(desc = __getOwnPropDesc(from, key)) || desc.enumerable,
        });
  }
  return to;
};
var __toESM = (mod, isNodeMode, target) => (
  (target = mod != null ? __create(__getProtoOf(mod)) : {}),
  __copyProps(
    // If the importer is in node compatibility mode or this is not an ESM
    // file that has been converted to a CommonJS file using a Babel-
    // compatible transform (i.e. "__esModule" has not been set), then set
    // "default" to the CommonJS "module.exports" for node compatibility.
    isNodeMode || !mod || !mod.__esModule
      ? __defProp(target, 'default', { value: mod, enumerable: true })
      : target,
    mod
  )
);
var import_autoload = __toESM(require('@fastify/autoload'));
var import_sensible = __toESM(require('@fastify/sensible'));
var import_fastify = __toESM(require('fastify'));
var import_fs = __toESM(require('fs'));
var import_path = __toESM(require('path'));
var import_jwt = __toESM(require('./plugins/jwt'));
var import_rate_limit = __toESM(require('./plugins/rate-limit'));
var import_package = __toESM(require('../package.json'));
const serviceName = import_package.default.name.replace('@twa/', '');
const httpsOptions = {
  key: import_fs.default.readFileSync(
    import_path.default.join(__dirname, '../certificates/localhost-key.pem')
  ),
  cert: import_fs.default.readFileSync(
    import_path.default.join(__dirname, '../certificates/localhost.pem')
  ),
};
const app = (0, import_fastify.default)({
  logger: true,
  https: httpsOptions,
  forceCloseConnections: true,
});
try {
  const afterRegister = (message) => (error) =>
    error ? app.log.error(error) : app.log.trace(message);
  app.register(import_sensible.default);
  app
    .register(import_autoload.default, {
      dir: (0, import_path.join)(__dirname, 'routes'),
    })
    .after(afterRegister('autoLoad plugin is ready.'));
  app.register(import_rate_limit.default).after(afterRegister('rateLimit plugin is ready.'));
  app.register(import_jwt.default).after(afterRegister('jwt plugin is ready.'));
  const start = async () => {
    const port = process.env.PORT ? parseInt(process.env.PORT, 10) : 3010;
    try {
      await app.listen({ port, host: '::' });
    } catch (err) {
      app.log.error(err);
      process.exit(1);
    }
  };
  start();
} catch (error) {
  const message = `${serviceName} dirty shutdown`;
  if (error instanceof Error) {
    app.log.error(error, message);
  } else {
    console.log(message, error);
  }
  process.exit(1);
}
