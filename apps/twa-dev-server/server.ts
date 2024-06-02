import fastifyHttpProxy from '@fastify/http-proxy';
import fastify from 'fastify';

const port = process.env.PORT ? parseInt(process.env.PORT, 10) : 8080;
const apiHost = 'http://localhost:3010';
const clientHost = 'http://localhost:3000';

const app = fastify({ logger: { level: 'trace' } });

app.register(fastifyHttpProxy, {
  upstream: apiHost + '/healthcheck',
  prefix: '/healthcheck',
  http2: false,
});

// api gateway
app.register(fastifyHttpProxy, {
  upstream: apiHost + '/v1/auth/signin',
  prefix: '/v1/auth/signin',
  http2: false,
});

app.register(fastifyHttpProxy, {
  upstream: apiHost + '/v1/auth/refresh',
  prefix: '/v1/auth/refresh',
  http2: false,
});

// client gateway
app.register(fastifyHttpProxy, {
  upstream: clientHost + '/',
  prefix: '/',
  http2: false,
});

app.listen({ port, host: '::' });
