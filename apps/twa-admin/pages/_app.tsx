import axios from 'axios';
import type { AppProps } from 'next/app';
import { Roboto, Roboto_Mono } from 'next/font/google';
import { useEffect, useState } from 'react';

import WebAppProvider from '../features/WebAppProvider/WebAppProvider';

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
  const [isHashValid, setIsHashValid] = useState(false);
  const [smoothButtonsTransition] = useState(false);

  // Wait for validation to complete before rendering the page and stop the
  // rendering if the hash is invalid. Comment out the following useEffect
  // hook to see the page render without the hash validation.
  useEffect(() => {
    window?.Telegram?.WebApp?.setHeaderColor?.('#000000');
    window?.Telegram?.WebApp?.setBackgroundColor?.('#000000');
    axios
      .post('/api/validate-hash', {
        hash: window.Telegram?.WebApp.initDataUnsafe,
      })
      .then((response) => setIsHashValid(response.status === 200));
  }, []);

  if (!isHashValid) {
    return null;
  }

  return (
    <>
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
    </>
  );
}

export default MyApp;
