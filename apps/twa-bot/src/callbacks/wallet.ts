import { isTelegramUrl } from '@tonconnect/sdk';
import * as fs from 'fs';
import { t } from 'i18next';
import { CallbackQuery, InlineKeyboardButton } from 'node-telegram-bot-api';
import QRCode from 'qrcode';

import { bot } from '@/bot';
import { disconnectWallet, showWalletOptions } from '@/handlers/wallet';
import { backToMainKeyboard } from '@/inline_buttons/back';
import { getConnector } from '@/packages/ton-connect/connector';
import { getWalletInfo } from '@/packages/ton-connect/wallets';
import { CallbackAction } from '@/types/actions';
import { addTGReturnStrategy } from '@/utils/tools';

const onDisconnectWallet = async (query: CallbackQuery) => {
  const chatId = query.message.chat.id;
  const userId = query.from.id;
  const { backId } = JSON.parse(query.data);
  disconnectWallet({ chatId, backId, userId });
};

const onWalletSettings = async (query: CallbackQuery) => {
  const chatId = query.message.chat.id;
  const userId = query.from.id;
  const msgId = query.message.message_id;

  await showWalletOptions({ chatId, userId, backId: msgId });
};

async function onWalletClick(query: CallbackQuery, data: string): Promise<void> {
  const chatId = query.message!.chat.id;
  const connector = getConnector(chatId);

  const selectedWallet = await getWalletInfo(data);
  if (!selectedWallet) {
    return;
  }

  let buttonLink = connector.connect({
    bridgeUrl: selectedWallet.bridgeUrl,
    universalLink: selectedWallet.universalLink,
  });

  let qrLink = buttonLink;

  if (isTelegramUrl(selectedWallet.universalLink)) {
    buttonLink = addTGReturnStrategy(buttonLink, process.env.TELEGRAM_BOT_LINK!);
    qrLink = addTGReturnStrategy(qrLink, 'none');
  }

  const fileName = 'QR-code-' + Math.round(Math.random() * 10000000000);

  await QRCode.toFile(fileName, qrLink);

  await bot.sendPhoto(chatId, fileName, {
    reply_markup: {
      inline_keyboard: (
        [
          [
            {
              text: t('buttons.connect', { walletName: selectedWallet.name }),
              url: buttonLink,
            },
          ],
        ] as InlineKeyboardButton[][]
      ).concat(backToMainKeyboard()),
    },
    parse_mode: 'HTML',
  });

  await new Promise((r) => fs.rm(`./${fileName}`, r));
}

export const walletMenuCallbacks = {
  [CallbackAction.SelectWallet]: onWalletClick,
  [CallbackAction.DisconnectWallet]: onDisconnectWallet,
  [CallbackAction.WalletSettings]: onWalletSettings,
};
