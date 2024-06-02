import axios from 'axios';
import type { AppProps } from 'next/app';
import { Roboto, Roboto_Mono } from 'next/font/google';
import { useEffect, useState } from 'react';

import WebAppProvider from '../features/WebAppProvider/WebAppProvider';

import { useAuth } from '@/api/hooks/useAuth';
import { AppProviders } from '@/features/AppProviders';
import ThemeProvider from '@/theme';

const ROBOTO_TTF = Roboto({
  subsets: ['latin', 'cyrillic'],
  weight: ['100', '300', '400', '500', '700', '900'],
  variable: '--font-roboto',
});

const ROBOTO_MONO_TTF = Roboto_Mono({
  subsets: ['latin', 'cyrillic'],
  weight: ['100', '200', '300', '400', '500', '600', '700'],
  variable: '--font-roboto-mono',
});

function MyApp({ Component, pageProps }: AppProps) {
  const [smoothButtonsTransition] = useState(false);

  return (
    <AppProviders>
      <style jsx global>{`
        html {
          font-family: ${ROBOTO_TTF.style.fontFamily}, ${ROBOTO_MONO_TTF.style.fontFamily};
        }
      `}</style>

      <ThemeProvider>
        <WebAppProvider options={{ smoothButtonsTransition }}>
          <Component {...pageProps} />
        </WebAppProvider>
      </ThemeProvider>
    </AppProviders>
  );
}

export default MyApp;
