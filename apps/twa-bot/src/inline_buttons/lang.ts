import { t } from 'i18next';
import { InlineKeyboardButton } from 'node-telegram-bot-api';

import { CallbackAction } from '../types/actions';

export const langSettingButtons = ({
  backId,
}: { backId?: number } = {}): InlineKeyboardButton[][] => [
  [
    {
      text: t('buttons.change_lang'),
      callback_data: JSON.stringify({
        method: CallbackAction.ShowLangs,
        backId,
      }),
    },
  ],
];

export const setLangButtons = (): InlineKeyboardButton[][] => [
  [
    {
      text: t('buttons.english'),
      callback_data: JSON.stringify({
        method: CallbackAction.SetLang,
        lang: 'en',
      }),
    },
  ],
  [
    {
      text: t('buttons.russian'),
      callback_data: JSON.stringify({
        method: CallbackAction.SetLang,
        lang: 'ru',
      }),
    },
  ],
];
export const changeLangButtons = ({ backId }: { backId?: number }): InlineKeyboardButton[][] => [
  [
    {
      text: t('buttons.english'),
      callback_data: JSON.stringify({
        method: CallbackAction.ChangeLang,
        lang: 'en',
        backId,
      }),
    },
  ],
  [
    {
      text: t('buttons.russian'),
      callback_data: JSON.stringify({
        method: CallbackAction.ChangeLang,
        lang: 'ru',
        backId,
      }),
    },
  ],
];
