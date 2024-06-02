import { FastifyPluginAsync, FastifyReply, FastifyRequest } from 'fastify';

import { UserData } from '../../../entities/auth';
import { validateHash } from '../../../helpers/validate-hash';

type SigninRequestWithBody = FastifyRequest<{
  Body: UserData;
}>;

const authRoutes: FastifyPluginAsync = async (app): Promise<void> => {
  app.post('/', async function (req: SigninRequestWithBody, res: FastifyReply) {
    try {
      const { webAppData } = req.body;
      // await validateHash(webAppData);

      const userId = 432443;

      const accessToken = await res.accessSign({ userId, webAppData });
      const refreshToken = await res.refreshSign({ userId, webAppData });

      res.send({ accessToken, refreshToken });
    } catch (e) {
      req.log.error(e);
      return res.badRequest('Could not create user');
    }
  });
};

export default authRoutes;
