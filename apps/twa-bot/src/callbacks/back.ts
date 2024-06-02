import { CallbackQuery } from 'node-telegram-bot-api';

import { showMain } from '@/handlers/main';
import { goBack } from '@/handlers/navigation';
import { CallbackAction } from '@/types/actions';

const onBack = async (query: CallbackQuery): Promise<void> => {
  const chatId = query.message.chat.id;
  const userId = query.from.id;
  const backId = JSON.parse(query.data).backId;

  await goBack({ chatId, userId, backId });
};

const onBackToMain = async (query: CallbackQuery): Promise<void> => {
  const chatId = query.message.chat.id;
  const userId = query.from.id;

  await showMain({ chatId, userId });
};

export const backMenuCallbacks = {
  [CallbackAction.Back]: onBack,
  [CallbackAction.BackToMain]: onBackToMain,
};
