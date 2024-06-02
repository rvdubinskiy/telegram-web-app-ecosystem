import rateLimitPlugin from '@fastify/rate-limit';
import type { FastifyInstance } from 'fastify';
import fastifyPlugin from 'fastify-plugin';

const rateLimit = async (app: FastifyInstance) => {
  await app.register(rateLimitPlugin, {
    max: 100, // maximum number of requests within the time window
    timeWindow: '1 minute', // time window in which the max number of requests can be made
  });
};

export default fastifyPlugin(rateLimit);
