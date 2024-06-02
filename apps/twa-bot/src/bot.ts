import dotenv from 'dotenv';
import TelegramBot from 'node-telegram-bot-api';
import path from 'path';

dotenv.config({ path: path.resolve(__dirname, `../../../.env.local`) });

export const token = process.env.BOT_TOKEN;

export const bot = new TelegramBot(token, { polling: true });
