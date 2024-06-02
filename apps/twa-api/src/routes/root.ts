import { FastifyPluginAsync } from 'fastify';

const rootRoutes: FastifyPluginAsync = async (app): Promise<void> => {
  app.get('/', async function () {
    return { root: true };
  });
};

export default rootRoutes;
