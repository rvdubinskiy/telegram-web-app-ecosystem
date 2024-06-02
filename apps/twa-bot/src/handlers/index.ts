import { isTelegramUrl, UserRejectsError } from '@tonconnect/sdk';
import TelegramBot from 'node-telegram-bot-api';

import { bot } from '@/bot';
import { getConnector } from '@/packages/ton-connect/connector';
import { getWalletInfo } from '@/packages/ton-connect/wallets';
import { addTGReturnStrategy, pTimeout, pTimeoutException } from '@/utils/tools';

export async function handleSendTXCommand(msg: TelegramBot.Message): Promise<void> {
  const chatId = msg.chat.id;

  const connector = getConnector(chatId);

  await connector.restoreConnection();
  if (!connector.connected) {
    await bot.sendMessage(chatId, 'Connect wallet to send transaction');
    return;
  }

  pTimeout(
    connector.sendTransaction({
      validUntil: Math.round(
        (Date.now() + Number(process.env.DELETE_SEND_TX_MESSAGE_TIMEOUT_MS)) / 1000
      ),
      messages: [
        {
          amount: '1000000',
          address: '0:0000000000000000000000000000000000000000000000000000000000000000',
        },
      ],
    }),
    Number(process.env.DELETE_SEND_TX_MESSAGE_TIMEOUT_MS)
  )
    .then(() => {
      bot.sendMessage(chatId, `Transaction sent successfully`);
    })
    .catch((e) => {
      if (e === pTimeoutException) {
        bot.sendMessage(chatId, `Transaction was not confirmed`);
        return;
      }

      if (e instanceof UserRejectsError) {
        bot.sendMessage(chatId, `You rejected the transaction`);
        return;
      }

      bot.sendMessage(chatId, `Unknown error happened`);
    })
    .finally(() => connector.pauseConnection());

  let deeplink = '';
  const walletInfo = await getWalletInfo(connector.wallet!.device.appName);
  if (walletInfo) {
    deeplink = walletInfo.universalLink;
  }

  if (isTelegramUrl(deeplink)) {
    const url = new URL(deeplink);
    url.searchParams.append('startattach', 'tonconnect');
    deeplink = addTGReturnStrategy(url.toString(), process.env.TELEGRAM_BOT_LINK!);
  }

  await bot.sendMessage(
    chatId,
    `Open ${walletInfo?.name || connector.wallet!.device.appName} and confirm transaction`,
    {
      reply_markup: {
        inline_keyboard: [
          [
            {
              text: `Open ${walletInfo?.name || connector.wallet!.device.appName}`,
              url: deeplink,
            },
          ],
        ],
      },
    }
  );
}
