import { getBaseUrl } from '@twa/utils/src/getBaseUrl';
import axios from 'axios';
import type { AxiosRequestConfig } from 'axios';
import axiosRetry from 'axios-retry';

export const enum METHODS {
  DELETE = 'DELETE',
  GET = 'GET',
  PATCH = 'PATCH',
  POST = 'POST',
  PUT = 'PUT',
}

const client = axios.create({ baseURL: getBaseUrl('api'), params: {} });
axiosRetry(client, { retries: 3, retryDelay: (retry) => Math.pow(2, retry) * 1000 });

client.interceptors.request.use(
  (config) => {
    const accessToken = sessionStorage.getItem('accessToken');
    if (accessToken) {
      config.headers['Authorization'] = `Bearer ${accessToken}`;
    }
    return config;
  },
  (error) => {
    return Promise.reject(error);
  }
);

client.interceptors.response.use(
  (response) => response,
  async (error) => {
    const originalRequest = error.config;
    if (error.response.status === 403 && !originalRequest._retry) {
      originalRequest._retry = true;
      const refreshToken = sessionStorage.getItem('refreshToken');

      const { data } = await axios.post(getBaseUrl('api', '/v1/auth/refresh'), {
        refreshToken,
      });

      sessionStorage.setItem('accessToken', data.token);

      originalRequest.headers['Authorization'] = `Bearer ${data.token}`;

      return axios(originalRequest);
    }
    return Promise.reject(error);
  }
);

type ParamsType = AxiosRequestConfig & {
  disableRetry?: boolean;
};

export class ApiBase {
  static PathPrefixes = {
    ajax: '/v1',
  };

  public makeRequest<T>({ disableRetry, ...config }: ParamsType): Promise<T> {
    return client<T>({
      ...config,
      ...(disableRetry && {
        'axios-retry': {
          retries: 0,
        },
      }),
    })
      .then((response) => {
        if (response.status >= 200 && response.status < 300) {
          return response.data;
        }
        throw new Error(
          `An error with the code ${response.status} occurred when requesting the server.`
        );
      })
      .catch((error) => {
        throw error;
      });
  }
}

export const api = new ApiBase();
