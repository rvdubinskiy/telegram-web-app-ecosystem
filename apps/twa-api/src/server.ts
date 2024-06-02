import autoLoad from '@fastify/autoload';
import sensible from '@fastify/sensible';
import Fastify from 'fastify';
import fs from 'fs';
import path, { join } from 'path';

import jwt from './plugins/jwt';
import rateLimit from './plugins/rate-limit';
import packageJson from '../package.json' assert { type: 'json' };

const serviceName = packageJson.name.replace('@twa/', '');

const httpsOptions = {
  key: fs.readFileSync(path.join(__dirname, '../certificates/localhost-key.pem')),
  cert: fs.readFileSync(path.join(__dirname, '../certificates/localhost.pem')),
};

const app = Fastify({
  logger: true,
  https: httpsOptions,
  forceCloseConnections: true,
});

try {
  const afterRegister = (message: string) => (error: Error | null) =>
    error ? app.log.error(error) : app.log.trace(message);
  // Will load all routes under src/routes
  app.register(sensible);
  app
    .register(autoLoad, {
      dir: join(__dirname, 'routes'),
    })
    .after(afterRegister('autoLoad plugin is ready.'));
  app.register(rateLimit).after(afterRegister('rateLimit plugin is ready.'));
  app.register(jwt).after(afterRegister('jwt plugin is ready.'));

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
