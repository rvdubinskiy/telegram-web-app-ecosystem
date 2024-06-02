import { t } from 'i18next';

export const mixedTexts = {
  main: ({
    invited,
    wallet,
  }: {
    wallet?: string;
    invited?: number;
  } = {}) =>
    [
      t('message_texts.greeting'),
      /**
       * за подписку на канал 100, за чат ещё 100, за подписку на Твиттер ещё 100
       */
      t('message_texts.invites', { coins: invited * 100 + 100 + 100 + 100 }),
      wallet ? t('message_texts.wallet_address', { walletAddress: wallet }) : false,
    ]
      .filter(Boolean)
      .join('\n\n')
      .trim(),
};
