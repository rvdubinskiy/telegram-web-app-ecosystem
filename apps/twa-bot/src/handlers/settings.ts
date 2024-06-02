import { t } from 'i18next';

import { bot } from '@/bot';
import { backKeyboard } from '@/inline_buttons/back';
import { langSettingButtons } from '@/inline_buttons/lang';

export const goSettings = async ({ chatId, msgId }) => {
  await bot.editMessageText(t('message_texts.settings_greeting'), {
    reply_markup: {
      inline_keyboard: langSettingButtons({ backId: msgId }).concat(backKeyboard(msgId)),
    },
    parse_mode: 'HTML',
    chat_id: chatId,
    message_id: msgId,
  });
};
