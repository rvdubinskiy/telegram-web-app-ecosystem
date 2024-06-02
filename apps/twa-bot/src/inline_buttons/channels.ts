import { t } from 'i18next';

import { CallbackAction } from '../types/actions';

import { urlsConfig } from '@/consts/urls';

export const showChannelsButtons = ({ channelUrl }: { channelUrl?: string } = {}) => [
  [
    {
      text: t('buttons.сhannel_link'),
      url: channelUrl,
    },
  ],
  [
    {
      text: t('buttons.community_link'),
      url: urlsConfig.community.url,
    },
  ],
  [
    {
      text: t('buttons.twitter_link'),
      url: urlsConfig.twitter.url,
    },
  ],
  [
    {
      text: t('buttons.check_channels'),
      callback_data: JSON.stringify({
        method: CallbackAction.CheckChannels,
      }),
    },
  ],
];
