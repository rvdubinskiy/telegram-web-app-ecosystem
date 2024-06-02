export enum CommandMessage {
  START = '/start',
  CONNECT_WALLET = '/connect',
}

export enum CallbackAction {
  ConnectWallet = 'connect-wallet',
  WalletSettings = 'wallet-settings',
  CheckChannels = 'check-channels',
  ChooseWallet = 'choose-wallet',
  SelectWallet = 'select-wallet',
  DisconnectWallet = 'disconnect-wallet',
  SetLang = 'set-lang',
  GoSettings = 'go-settings',
  ShowLangs = 'show-langs',
  ChangeLang = 'change-lang',
  Back = 'back',
  BackToMain = 'back-to-main',
  InviteFriends = 'invite-friends',
}
