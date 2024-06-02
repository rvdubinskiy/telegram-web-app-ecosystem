import { CHAIN, toUserFriendlyAddress } from '@tonconnect/sdk';
import { t } from 'i18next';

import { goBack } from './navigation';

import { bot } from '@/bot';
import { backKeyboard } from '@/inline_buttons/back';
import { walletOptionsKeyboard } from '@/inline_buttons/wallet';
import { User } from '@/models';
import { getConnector } from '@/packages/ton-connect/connector';

export const showWalletOptions = async ({ chatId, userId, backId }) => {
  try {
    const connector = getConnector(chatId);

    await connector.restoreConnection();

    const wallet = toUserFriendlyAddress(
      connector.wallet?.account.address,
      connector.wallet?.account.chain === CHAIN.MAINNET
    );
    const text = [
      t('message_texts.wallet_options_title'),
      wallet ? t('message_texts.wallet_address', { walletAddress: wallet }) : false,
    ]
      .filter(Boolean)
      .join('\n\n')
      .trim();

    await bot.editMessageText(text, {
      reply_markup: {
        inline_keyboard: walletOptionsKeyboard({ backId }).concat(backKeyboard(backId)),
      },
      parse_mode: 'HTML',
      chat_id: chatId,
      message_id: backId,
    });
  } catch (e) {
    console.error(e);
  }
};

export const disconnectWallet = async ({ chatId, userId, backId }): Promise<void> => {
  try {
    const connector = getConnector(chatId);

    await connector.restoreConnection();
    if (!connector.connected) {
      return;
    }

    await User.updateOne(
      { telegram_id: userId },
      {
        $set: {
          wallet: {},
        },
      }
    );

    await connector.disconnect();

    await goBack({ chatId, backId, userId });
  } catch (e) {
    console.error(e);
  }
};
