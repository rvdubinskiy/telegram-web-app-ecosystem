import { encodeTelegramUrlParameters, isTelegramUrl, WalletInfoRemote } from '@tonconnect/sdk';
import { t } from 'i18next';
import { InlineKeyboardButton } from 'node-telegram-bot-api';

import { CallbackAction } from '@/types/actions';

export const AT_WALLET_APP_NAME = 'telegram-wallet';

export const pTimeoutException = Symbol();

export function pTimeout<T>(
  promise: Promise<T>,
  time: number,
  exception: unknown = pTimeoutException
): Promise<T> {
  let timer: ReturnType<typeof setTimeout>;
  return Promise.race([
    promise,
    new Promise((_r, rej) => (timer = setTimeout(rej, time, exception))),
  ]).finally(() => clearTimeout(timer)) as Promise<T>;
}

export function addTGReturnStrategy(link: string, strategy: string): string {
  const parsed = new URL(link);
  parsed.searchParams.append('ret', strategy);
  link = parsed.toString();

  const lastParam = link.slice(link.lastIndexOf('&') + 1);
  return link.slice(0, link.lastIndexOf('&')) + '-' + encodeTelegramUrlParameters(lastParam);
}

export function convertDeeplinkToUniversalLink(link: string, walletUniversalLink: string): string {
  const search = new URL(link).search;
  const url = new URL(walletUniversalLink);

  if (isTelegramUrl(walletUniversalLink)) {
    const startattach = 'tonconnect-' + encodeTelegramUrlParameters(search.slice(1));
    url.searchParams.append('startattach', startattach);
  } else {
    url.search = search;
  }

  return url.toString();
}

export async function buildUniversalKeyboard(
  link: string,
  wallets: WalletInfoRemote[],
  backId?: number
): Promise<InlineKeyboardButton[][]> {
  const atWallet = wallets.find((wallet) => wallet.appName.toLowerCase() === AT_WALLET_APP_NAME);
  const atWalletLink = atWallet
    ? addTGReturnStrategy(
        convertDeeplinkToUniversalLink(link, atWallet?.universalLink),
        process.env.TELEGRAM_BOT_LINK!
      )
    : undefined;

  const keyboard = [
    // [
    //   {
    //     text: t('buttons.choose_another_wallet'),
    //     callback_data: JSON.stringify({ method: CallbackAction.ChooseWallet, backId }),
    //   },
    // ],
    // [
    //   {
    //     text: t('buttons.outer_wallet_link'),
    //     url: `https://ton-connect.github.io/open-tc?connect=${encodeURIComponent(link)}`,
    //   },
    // ],
  ];

  if (atWalletLink) {
    keyboard.unshift([
      {
        text: t('buttons.ton_wallet'),
        url: atWalletLink,
      },
    ]);
  }

  return keyboard;
}
