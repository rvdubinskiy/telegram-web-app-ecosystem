import { t } from 'i18next';
import { InlineKeyboardButton } from 'node-telegram-bot-api';

import { CallbackAction } from '../types/actions';

export const walletOptionsKeyboard = ({
  backId,
}: { backId?: number } = {}): InlineKeyboardButton[][] => [
  [
    {
      text: t('buttons.disconnect_wallet'),
      callback_data: JSON.stringify({ method: CallbackAction.DisconnectWallet, backId }),
    },
  ],
];
