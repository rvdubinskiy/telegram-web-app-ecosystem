// import type { TelegramWebApps } from 'telegram-webapps-types';

import { WebApp } from '../core/twa-types';

declare global {
  interface Window {
    Telegram?: {
      WebApp: WebApp;
    };
    TelegramWebviewProxy?: any;
  }

  namespace NodeJS {
    interface ProcessEnv {
      /** Authorization token for the bot. This is used to validate the hash's authenticity. */
      BOT_TOKEN: string;
    }
  }
}

export {};
