import { FastifyPluginAsync } from 'fastify';

const healthcheckRoutes: FastifyPluginAsync = async (app): Promise<void> => {
  app.get('/', (_, res) => {
    res.send({ message: 'ok' });
  });
};

export default healthcheckRoutes;
