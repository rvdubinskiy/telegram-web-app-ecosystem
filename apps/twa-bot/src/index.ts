import dotenv from 'dotenv';
import { changeLanguage, t } from 'i18next';
import path from 'path';

import { showChannelsList } from './handlers/channels';
import { showMain } from './handlers/main';
import { setLangButtons } from './inline_buttons/lang';
import { User } from './models';
import { initI18n, normalizeLang } from './utils/i18n';

import { bot } from '@/bot';
import { backMenuCallbacks } from '@/callbacks/back';
import { channelsMenuCallbacks } from '@/callbacks/channels';
import { langMenuCallbacks } from '@/callbacks/lang';
import { mainMenuCallbacks } from '@/callbacks/main';
import { walletMenuCallbacks } from '@/callbacks/wallet';
import { initRedisClient } from '@/packages/ton-connect/storage';
import { connectToDatabase } from '@/utils/mongodb';

dotenv.config({ path: path.resolve(__dirname, `../../../.env.local`) });

let restarts = 0;
(async function run() {
  try {
    try {
      await connectToDatabase(process.env.MONGO_URL);
      await initRedisClient();
    } catch (e) {
      console.error(e);
    }

    try {
      initI18n();
    } catch (e) {
      console.error(e);
    }

    const callbacks = {
      ...langMenuCallbacks,
      ...channelsMenuCallbacks,
      ...mainMenuCallbacks,
      ...walletMenuCallbacks,
      ...backMenuCallbacks,
    };

    bot.on('message', async (msg) => {
      const userId = msg.from.id;
      const maybeUser = await User.findOne({ telegram_id: userId });

      if (maybeUser && maybeUser.lang_code) {
        await changeLanguage(maybeUser.lang_code);
      }
    });

    bot.onText(/\/start/, async (msg) => {
      const chatId = msg.chat.id;
      const msgId = msg.message_id;
      const userId = msg.from.id;

      const maybeInvite = msg.text?.split('r_')?.[1] ?? null;

      const userData = {
        telegram_id: userId,
        first_name: msg.from.first_name,
        last_name: msg.from.last_name,
        username: msg.from.username,
        is_premium: false,
        is_bot: msg.from.is_bot,
        lang_code: msg.from.language_code,
        is_subscribed: false,
        created_at: new Date().toISOString(),
      };

      try {
        const maybeUser = await User.findOne({ telegram_id: userId });
        if (!maybeUser) {
          const user = await User.create(userData);

          const lang = normalizeLang(userData.lang_code);

          await changeLanguage(lang);

          await bot.sendMessage(chatId, t('message_texts.choose_language'), {
            reply_markup: {
              inline_keyboard: setLangButtons(),
            },
            parse_mode: 'HTML',
          });

          if (!maybeInvite) return;

          const inviteHostId = Number(maybeInvite);

          if (typeof inviteHostId !== 'number' || inviteHostId <= 0) return;

          await User.updateOne(
            { telegram_id: inviteHostId },
            {
              $addToSet: {
                invites: user._id,
              },
            }
          );
        } else if (maybeUser.is_subscribed) {
          showMain({ chatId, userId });
        } else {
          showChannelsList({ chatId, userId });
        }
      } catch (e) {
        console.error(e);
      }
    });

    bot.onText(/\/profile/, async (msg) => {
      const chatId = msg.chat.id;
      const userId = msg.from.id;

      try {
        const maybeUser = await User.findOne({ telegram_id: userId });
        if (maybeUser && maybeUser.is_subscribed) {
          showMain({ chatId, userId });
        }
      } catch (e) {
        console.error(e);
      }
    });

    bot.on('callback_query', (query) => {
      if (!query.data) {
        return;
      }

      let request: { method: string; data: string };

      try {
        request = JSON.parse(query.data);
      } catch {
        return;
      }

      if (!callbacks[request.method as keyof typeof callbacks]) {
        return;
      }

      callbacks[request.method as keyof typeof callbacks](query, request.data);
    });
  } catch (e) {
    console.error(e);

    if (restarts > 5) {
      throw new Error('Restarts more than 5 -> exit');
    }

    ++restarts;

    run();
  }
})();
