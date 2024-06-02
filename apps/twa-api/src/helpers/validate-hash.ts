import { InitDataUnsafe } from '@twa/entities/src/webapp/types';
import { webcrypto } from 'crypto';
import { FastifyReply, FastifyRequest } from 'fastify';

type Data = { ok: boolean } | { error: string };

export default async function handler(
  req: FastifyRequest<{ Body: { initData: any } }>,
  res: FastifyReply
) {
  if (req.method !== 'POST') {
    return res.status(405).send(JSON.stringify({ error: 'Method not allowed' }));
  }

  if (!req.body.initData) {
    return res.status(400).send(
      JSON.stringify({
        error: 'Missing required field hash',
      })
    );
  }

  if (!process.env.BOT_TOKEN) {
    return res.status(500).send(JSON.stringify({ error: 'Internal server error' }));
  }

  const data = { ...req.body.initData, user: JSON.stringify(req.body.initData.user) };
  const isValid = await isHashValid(data, process.env.BOT_TOKEN);

  if (isValid) {
    return res.status(200).send(JSON.stringify({ ok: true }));
  }

  return res.status(403).send(JSON.stringify({ error: 'Invalid hash' }));
}

export const validateHash = async (initData: InitDataUnsafe) => {
  if (!initData) {
    throw new Error('Missing required field hash');
  }

  if (!process.env.BOT_TOKEN) {
    throw new Error('Internal server error');
  }

  const data = {
    hash: initData.hash,
    auth_date: String(initData.auth_date),
    user: JSON.stringify(initData.user),
  };
  const isValid = await isHashValid(data, process.env.BOT_TOKEN);

  if (isValid) {
    return true;
  }

  throw new Error('Invalid hash');
};

async function isHashValid(data: Record<string, string>, botToken: string) {
  const encoder = new TextEncoder();

  const checkString = Object.keys(data)
    .filter((key) => key !== 'hash')
    .map((key) => `${key}=${data[key]}`)
    .sort()
    .join('\n');

  const secretKey = await webcrypto.subtle.importKey(
    'raw',
    encoder.encode('WebAppData'),
    { name: 'HMAC', hash: 'SHA-256' },
    true,
    ['sign']
  );

  const secret = await webcrypto.subtle.sign('HMAC', secretKey, encoder.encode(botToken));

  const signatureKey = await webcrypto.subtle.importKey(
    'raw',
    secret,
    { name: 'HMAC', hash: 'SHA-256' },
    true,
    ['sign']
  );

  const signature = await webcrypto.subtle.sign('HMAC', signatureKey, encoder.encode(checkString));

  const hex = Buffer.from(signature).toString('hex');

  return data.hash === hex;
}
