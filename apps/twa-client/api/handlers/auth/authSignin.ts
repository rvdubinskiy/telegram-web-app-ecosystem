import { getBaseUrl } from '@twa/utils/src/getBaseUrl';

import { METHODS, api } from '@/api/Api';

export interface SigninData {
  initData: any;
}

interface SigninResponse {
  accessToken: string;
  refreshToken: string;
}

export const authSigninHandler = (data: SigninData) => {
  const { initData } = data;

  console.log(getBaseUrl('api', '/v1/auth/signin'));

  return api.makeRequest<SigninResponse>({
    url: getBaseUrl('api', '/v1/auth/signin'),
    method: METHODS.POST,
    headers: {
      'content-type': 'application/json',
    },
    data: JSON.stringify({ initData }),
  });
};
