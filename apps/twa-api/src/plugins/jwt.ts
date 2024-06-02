import fJwt from '@fastify/jwt';
import { randomUUID } from 'crypto';
import { FastifyInstance, FastifyRequest, FastifyReply } from 'fastify';
import fastifyPlugin from 'fastify-plugin';

import { refresh } from '../helpers/refresh';

const publicRoutes = ['/healthcheck', '/v1/auth', '/v1/auth/refresh'];
const ACCESS_SECRET =
  'lopEjWIKZwHYNTqm+1ZmXvZCUyyvTUQcPUUt7ppP5y5nM7b54mykuhPEyrO3U3m+L71hXkaOMRcF28cJOIQBWmpCA8nN4DGVPkoPEQh1FQChWvSfRWxo3i3OJYxC2DfejlLuVOFBSEQyU0igQvbtHmKMCF9Dpzj6+v9DOnr6uK9YleePzvlKtFwEQsLbldfqGzEbhyoo1t0AsULfDQDkw6HBhQn3Uw7qIcXD458wwW4CdqIPv0SV81bLGhBtSs313jDVxY/YZ6DhjRkDeUmMdBEarwQ/h6feTvD+b5CeJ2ZAUe5kec+FcrunsK2e6mEertI4QhfVRuJKY1petRxhSQ==';
const REFRESH_SECRET =
  'lopEjWIKZwHYNTqm+1ZmXvZCUyyvTUQcPUUt7ppP5y5nM7b54mykuhPEyrO3U3m+L71hXkaOMRcF28cJOIQBWmpCA8nN4DGVPkoPEQh1FQChWvSfRWxo3i3OJYxC2DfejlLuVOFBSEQyU0igQvbtHmKMCF9Dpzj6+v9DOnr6uK9YleePzvlKtFwEQsLbldfqGzEbhyoo1t0AsULfDQDkw6HBhQn3Uw7qIcXD458wwW4CdqIPv0SV81bLGhBtSs313jDVxY/YZ6DhjRkDeUmMdBEarwQ/h6feTvD+b5CeJ2ZAUe5kec+FcrunsK2e6mEertI4QhfVRuJKY1petRxhSQ==';

const jwt = async (app: FastifyInstance) => {
  await app.register(fJwt, {
    secret: ACCESS_SECRET,
    sign: {
      algorithm: 'HS256',
      expiresIn: '10d',
    },
    namespace: 'access',
    jwtVerify: 'accessVerify',
    jwtSign: 'accessSign',
  });

  await app.register(fJwt, {
    secret: REFRESH_SECRET,
    sign: {
      algorithm: 'HS256',
      expiresIn: '30d',
      jti: randomUUID(),
    },
    namespace: 'refresh',
    jwtVerify: 'refreshVerify',
    jwtSign: 'refreshSign',
    jwtDecode: 'refreshDecode',
  });

  app.addHook('onRequest', async (req: FastifyRequest, reply: FastifyReply) => {
    const route = req.url ?? '';

    if (publicRoutes.includes(route)) {
      return;
    }

    if (!req.headers.authorization || req.headers.authorization.split(' ')[0] !== 'Bearer') {
      return reply.unauthorized('Must include a Bearer authorization.');
    }
    try {
      await req.accessVerify();
    } catch (e) {
      req.log.error(e);
      const { error, message } = await refresh(req, reply);
      if (error) {
        return reply.unauthorized(message);
      }
    }
  });
};

export default fastifyPlugin(jwt);
