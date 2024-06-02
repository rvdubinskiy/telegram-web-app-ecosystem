import { t } from 'i18next';
import { CallbackQuery, InlineKeyboardButton } from 'node-telegram-bot-api';
import QRCode from 'qrcode';

import { bot } from '@/bot';
import { showMain } from '@/handlers/main';
import { goSettings } from '@/handlers/settings';
import { backKeyboard, backToMainKeyboard } from '@/inline_buttons/back';
import { langSettingButtons } from '@/inline_buttons/lang';
import { User } from '@/models';
import { getConnector } from '@/packages/ton-connect/connector';
import { getWallets, getWalletInfo } from '@/packages/ton-connect/wallets';
import { CallbackAction } from '@/types/actions';
import { buildUniversalKeyboard } from '@/utils/tools';

const newConnectRequestListenersMap = new Map<number, () => void>();

const onConnectWallet = async (query: CallbackQuery, _: string): Promise<void> => {
  const msg = query.message;
  const chatId = msg.chat.id;
  const userId = msg.from.id;
  let messageWasDeleted = false;

  newConnectRequestListenersMap.get(chatId)?.();

  const connector = getConnector(chatId, async () => {
    unsubscribe();

    newConnectRequestListenersMap.delete(chatId);

    deleteMessage();
  });

  await connector.restoreConnection();
  if (connector.connected) {
    await showMain({ chatId, userId });

    return;
  }

  const unsubscribe = connector.onStatusChange(async (wallet) => {
    if (wallet) {
      await deleteMessage();

      const walletName =
        (await getWalletInfo(wallet.device.appName))?.name || wallet.device.appName;

      await bot.sendMessage(chatId, t('message_texts.wallet_connect_success', { walletName }));

      unsubscribe();
      newConnectRequestListenersMap.delete(chatId);
    }
  });

  const wallets = await getWallets();

  const link = connector.connect(wallets);
  const image = await QRCode.toBuffer(link);

  const keyboard = await buildUniversalKeyboard(link, wallets);

  const botMessage = await bot.sendPhoto(chatId, image, {
    reply_markup: {
      inline_keyboard: keyboard,
    },
  });

  const deleteMessage = async (): Promise<void> => {
    if (!messageWasDeleted) {
      messageWasDeleted = true;
      await bot.deleteMessage(chatId, botMessage.message_id);
    }
  };

  newConnectRequestListenersMap.set(chatId, async () => {
    unsubscribe();

    await deleteMessage();

    newConnectRequestListenersMap.delete(chatId);
  });
};

async function onChooseWalletClick(query: CallbackQuery, _: string): Promise<void> {
  const chatId = query.message?.chat.id;
  const msgId = query.message?.message_id;
  const userId = query.from.id;
  const wallets = await getWallets();

  const walletButtons = wallets.map((wallet) => ({
    text: wallet.name,
    callback_data: JSON.stringify({
      method: CallbackAction.SelectWallet,
      data: wallet.appName,
    }),
  }));

  await bot.editMessageText(t('message_texts.choose_wallet'), {
    reply_markup: {
      inline_keyboard: (
        [walletButtons.slice(0, 2), walletButtons.slice(2, 4)] as InlineKeyboardButton[][]
      ).concat(backKeyboard(msgId)),
    },
    message_id: msgId,
    chat_id: chatId,
  });

  const connector = getConnector(chatId);

  await connector.restoreConnection();

  const unsubscribe = connector.onStatusChange(async (wallet) => {
    if (wallet) {
      const walletName =
        (await getWalletInfo(wallet.device.appName))?.name || wallet.device.appName;

      await User.updateOne(
        { telegram_id: userId },
        {
          $set: {
            wallet: {
              chain: wallet.account.chain,
              address: wallet.account.address,
              walletName,
            },
          },
        }
      );
      // Notify via Telegram bot
      await bot.sendMessage(chatId, t('message_texts.wallet_connect_success', { walletName }), {
        reply_markup: {
          inline_keyboard: backToMainKeyboard(),
        },
      });

      unsubscribe();
    }
  });
}

const onGoSettings = async (query: CallbackQuery) => {
  const chatId = query.message.chat.id;
  const msgId = query.message.message_id;
  await goSettings({ chatId, msgId });
};

export const mainMenuCallbacks = {
  [CallbackAction.GoSettings]: onGoSettings,
  [CallbackAction.ConnectWallet]: onConnectWallet,
  [CallbackAction.ChooseWallet]: onChooseWalletClick,
};
