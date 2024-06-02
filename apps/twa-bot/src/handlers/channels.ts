import { t } from 'i18next';

import image from '@/assets/join_club.png';
import { bot } from '@/bot';
import { urlsConfig } from '@/consts/urls';
import { showChannelsButtons } from '@/inline_buttons/channels';
import { User } from '@/models';
import { normalizeLang } from '@/utils/i18n';

export const showChannelsList = async ({ chatId, userId }) => {
  const user = await User.findOne({ telegram_id: userId });

  if (!user) return;

  const channelUrl =
    normalizeLang(user.lang_code) === 'en' ? urlsConfig.enChannel.url : urlsConfig.ruChannel.url;
  await bot.sendPhoto(chatId, Buffer.from(image, 'base64'), {
    caption: t('message_texts.subscribe_resources'),
    reply_markup: {
      inline_keyboard: showChannelsButtons({ channelUrl }),
    },
    parse_mode: 'HTML',
  });
};
