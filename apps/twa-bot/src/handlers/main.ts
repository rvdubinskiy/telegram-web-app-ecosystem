import { CHAIN, toUserFriendlyAddress } from '@tonconnect/sdk';

import { bot } from '@/bot';
import { mainButtons } from '@/inline_buttons/main';
import { User } from '@/models';
import { getConnector } from '@/packages/ton-connect/connector';
import { mixedTexts } from '@/texts/actions';

export const showMain = async ({ chatId, userId }) => {
  const user = await User.findOne({ telegram_id: userId });

  if (!user) return;

  const invites = user.invites.length;

  const connector = getConnector(chatId);

  await connector.restoreConnection();

  const wallet = connector.connected
    ? toUserFriendlyAddress(
        connector.wallet?.account.address,
        connector.wallet?.account.chain === CHAIN.MAINNET
      )
    : null;

  bot.sendMessage(chatId, mixedTexts.main({ invited: invites, wallet }), {
    reply_markup: {
      inline_keyboard: mainButtons({ id: userId, isWallet: connector.connected }),
    },
    parse_mode: 'HTML',
  });
};
