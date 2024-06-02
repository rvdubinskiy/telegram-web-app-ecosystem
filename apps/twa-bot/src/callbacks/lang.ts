import { changeLanguage, t } from 'i18next';
import { CallbackQuery } from 'node-telegram-bot-api';

import { bot } from '@/bot';
import { showChannelsList } from '@/handlers/channels';
import { goBack } from '@/handlers/navigation';
import { backKeyboard } from '@/inline_buttons/back';
import { changeLangButtons } from '@/inline_buttons/lang';
import { User } from '@/models';
import { CallbackAction } from '@/types/actions';

const onSetLang = async (query: CallbackQuery): Promise<void> => {
  const chatId = query.message.chat.id;
  const msgId = query.message.message_id;
  const userId = query.from.id;
  const lang = JSON.parse(query.data).lang;

  try {
    await changeLanguage(lang);

    await User.findOneAndUpdate(
      { telegram_id: userId },
      {
        $set: {
          lang_code: lang,
        },
      }
    );

    await bot.deleteMessage(chatId, msgId);

    await showChannelsList({ chatId, userId });
  } catch (e) {
    console.log(e);
  }
};

const onChangeLang = async (query: CallbackQuery): Promise<void> => {
  const chatId = query.message.chat.id;
  const userId = query.from.id;
  const { lang, backId } = JSON.parse(query.data);

  try {
    await changeLanguage(lang);

    await User.findOneAndUpdate(
      { telegram_id: userId },
      {
        $set: {
          lang_code: lang,
        },
      }
    );

    await goBack({ chatId, backId, userId });
  } catch (e) {
    console.log(e);
  }
};

const onShowLangs = async (query: CallbackQuery): Promise<void> => {
  const chatId = query.message.chat.id;
  const msgId = query.message.message_id;

  try {
    bot.editMessageText(t('message_texts.choose_language'), {
      reply_markup: {
        inline_keyboard: changeLangButtons({ backId: msgId }).concat(backKeyboard(msgId)),
      },
      parse_mode: 'HTML',
      chat_id: chatId,
      message_id: msgId,
    });
  } catch (e) {
    console.log(e);
  }
};

export const langMenuCallbacks = {
  [CallbackAction.SetLang]: onSetLang,
  [CallbackAction.ChangeLang]: onChangeLang,
  [CallbackAction.ShowLangs]: onShowLangs,
};
