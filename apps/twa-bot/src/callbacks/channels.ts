import { t } from 'i18next';
import { CallbackQuery } from 'node-telegram-bot-api';

import { bot } from '@/bot';
import { urlsConfig } from '@/consts/urls';
import { showMain } from '@/handlers/main';
import { showChannelsButtons } from '@/inline_buttons/channels';
import { User } from '@/models';
import { CallbackAction } from '@/types/actions';
import { normalizeLang } from '@/utils/i18n';

const onCheckChannels = async (query: CallbackQuery): Promise<void> => {
  const chatId = query.message.chat.id;
  const msgId = query.message.message_id;
  const userId = query.from.id;

  const user = await User.findOne({ telegram_id: userId });

  if (!user) return;

  const channelUrl =
    normalizeLang(user.lang_code) === 'en' ? urlsConfig.enChannel.url : urlsConfig.ruChannel.url;
  const channelId =
    normalizeLang(user.lang_code) === 'en' ? urlsConfig.enChannel.id : urlsConfig.ruChannel.id;

  try {
    const isChannelMember = await bot.getChatMember(channelId, userId);

    if (!isChannelMember || ['restricted', 'left', 'kicked'].includes(isChannelMember.status))
      throw new Error('No user in channel');

    try {
      const isChatMember = await bot.getChatMember(urlsConfig.community.id, userId);

      if (!isChatMember || ['restricted', 'left', 'kicked'].includes(isChatMember.status))
        throw new Error('No user in chat');

      await bot.sendMessage(chatId, t('message_texts.access_allowed'));

      await showMain({ chatId, userId });

      await User.findOneAndUpdate(
        { telegram_id: userId },
        {
          $set: {
            is_subscribed: true,
          },
        }
      );

      await bot.deleteMessage(chatId, msgId);
    } catch (e) {
      console.log(e);
      await bot.sendMessage(chatId, t('message_texts.access_denied_cause_chat'), {
        reply_markup: {
          inline_keyboard: showChannelsButtons({ channelUrl }),
        },
        parse_mode: 'HTML',
      });
    }
  } catch (e) {
    console.error(e);
    await bot.sendMessage(chatId, t('message_texts.access_denied_cause_channel'), {
      reply_markup: {
        inline_keyboard: showChannelsButtons({ channelUrl }),
      },
      parse_mode: 'HTML',
    });
  }
};

export const channelsMenuCallbacks = {
  [CallbackAction.CheckChannels]: onCheckChannels,
};
