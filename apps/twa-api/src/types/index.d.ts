import 'fastify';

declare module 'fastify' {
  interface FastifyInstance {
    authorize: (req: FastifyRequest, reply: FastifyReply) => void | Promise<void>;
  }

  interface FastifyRequest {
    accessVerify: FastifyRequest['jwtVerify'];
    refreshVerify: FastifyRequest['jwtVerify'];
    refreshDecode: FastifyRequest['jwtDecode'];
  }

  interface FastifyReply {
    accessSign: FastifyReply['jwtSign'];
    refreshSign: FastifyReply['jwtSign'];
  }
}
