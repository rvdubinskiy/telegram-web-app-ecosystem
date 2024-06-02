import i18next from 'i18next';
import Backend from 'i18next-fs-backend';

import en from '../locales/en.json';
import ru from '../locales/ru.json';

import { Lang } from '@/types/i18n';

const DEFAULT_LANG = 'en';

export const initI18n = () => {
  // Initialize i18next
  i18next.use(Backend).init(
    {
      lng: DEFAULT_LANG, // Default language
      fallbackLng: DEFAULT_LANG, // Fallback language
      resources: {
        en,
        ru,
      },
    },
    (err) => {
      if (err) return console.error(err);
      console.log('i18next is ready...');
    }
  );
};

export const normalizeLang = (lang?: string): Lang => {
  switch (lang) {
    case 'ru':
      return 'ru';

    case 'en':
      return 'en';

    default:
      return DEFAULT_LANG;
  }
};
