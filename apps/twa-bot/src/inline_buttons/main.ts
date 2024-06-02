import { t } from 'i18next';
import { InlineKeyboardButton } from 'node-telegram-bot-api';

import { CallbackAction } from '../types/actions';

const WEB_APP_URL = process.env.twa_CLIENT_BASEURL;

export const mainButtons = ({
  id,
  backId,
  isWallet,
}: { id?: number; backId?: number; isWallet?: boolean } = {}): InlineKeyboardButton[][] => [
  [
    isWallet
      ? {
          text: t('buttons.wallet_settings'),
          callback_data: JSON.stringify({
            method: CallbackAction.WalletSettings,
            backId,
          }),
        }
      : {
          text: t('buttons.connect_wallet'),
          callback_data: JSON.stringify({
            method: CallbackAction.ChooseWallet,
            backId,
          }),
        },
  ],
  [
    {
      text: t('buttons.invite_friends'),
      url: `https://t.me/share/url?url=https://t.me/titscoin_bot?start=r_${id}&text=${encodeURIComponent(
        t('message_texts.invite_greeting')
      )}`,
    },
    {
      text: t('buttons.settings'),
      callback_data: JSON.stringify({
        method: CallbackAction.GoSettings,
        backId,
      }),
    },
  ],
  // [
  //   {
  //     text: keyboardTexts.play,
  //     wep_app: {
  //       url: WEB_APP_URL,
  //     },
  //   },
  // ],
];
