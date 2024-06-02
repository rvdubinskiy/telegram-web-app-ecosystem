import { FastifyReply, FastifyRequest } from 'fastify';

import { DecodedUserData } from '../entities/auth';

export type RefreshReply =
  | {
      message: undefined;
      accessToken: string;
      refreshToken: string;
      error: boolean;
      decoded: DecodedUserData;
    }
  | {
      message: string;
      accessToken: null;
      refreshToken: null;
      error: boolean;
      decoded: DecodedUserData;
    };

export const refresh = async (req: FastifyRequest, reply: FastifyReply): Promise<RefreshReply> => {
  const { payload: decodedPayload } = await req.refreshVerify<{
    payload: DecodedUserData;
  }>({
    complete: true,
  });

  // Sign new access token
  const accessToken = await reply.accessSign(decodedPayload);

  // Sign new refresh token
  const refreshToken = await reply.refreshSign(decodedPayload);

  return {
    decoded: decodedPayload,
    accessToken,
    refreshToken,
    error: true,
    message: undefined,
  };
};
