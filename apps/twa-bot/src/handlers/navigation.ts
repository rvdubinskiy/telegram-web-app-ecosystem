import { CHAIN, toUserFriendlyAddress } from '@tonconnect/sdk';

import { bot } from '@/bot';
import { mainButtons } from '@/inline_buttons/main';
import { User } from '@/models';
import { getConnector } from '@/packages/ton-connect/connector';
import { mixedTexts } from '@/texts/actions';

export const goBack = async ({ chatId, userId, backId }) => {
  try {
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

    bot.editMessageText(mixedTexts.main({ invited: invites, wallet }), {
      chat_id: chatId,
      message_id: backId,
      reply_markup: {
        inline_keyboard: mainButtons({ id: userId, isWallet: connector.connected }),
      },
      parse_mode: 'HTML',
    });
  } catch (e) {
    console.error(e);
  }
};
