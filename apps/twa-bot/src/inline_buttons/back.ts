import { t } from 'i18next';
import { InlineKeyboardButton } from 'node-telegram-bot-api';

import { CallbackAction } from '../types/actions';

export const backKeyboard = (backId?: number): InlineKeyboardButton[][] => [
  [
    {
      text: t('buttons.back'),
      callback_data: JSON.stringify({ method: CallbackAction.Back, backId }),
    },
  ],
];

export const backToMainKeyboard = (): InlineKeyboardButton[][] => [
  [
    {
      text: t('buttons.back'),
      callback_data: JSON.stringify({ method: CallbackAction.BackToMain }),
    },
  ],
];
