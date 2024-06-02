import type {Theme} from '@mui/material/styles'

// ----------------------------------------------------------------------

export function CssBaseline(theme: Theme) {
  return {
    MuiCssBaseline: {
      styleOverrides: `
      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-black.woff2') format('woff2'), url('/fonts/suisseintl-black.woff') format('woff');
          font-weight: 900;
          font-style: normal;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-blackitalic.woff2') format('woff2'), url('/fonts/suisseintl-blackitalic.woff') format('woff');
          font-weight: 900;
          font-style: italic;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-bold.woff2') format('woff2'), url('/fonts/suisseintl-bold.woff') format('woff');
          font-weight: 700;
          font-style: normal;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-bolditalic.woff2') format('woff2'), url('/fonts/suisseintl-bolditalic.woff') format('woff');
          font-weight: 700;
          font-style: italic;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-semibold.woff2') format('woff2'), url('/fonts/suisseintl-semibold.woff') format('woff');
          font-weight: 600;
          font-style: normal;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-semibolditalic.woff2') format('woff2'), url('/fonts/suisseintl-semibolditalic.woff') format('woff');
          font-weight: 600;
          font-style: italic;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-medium.woff2') format('woff2'), url('/fonts/suisseintl-medium.woff') format('woff');
          font-weight: 500;
          font-style: normal;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-mediumitalic.woff2') format('woff2'), url('/fonts/suisseintl-mediumitalic.woff') format('woff');
          font-weight: 500;
          font-style: italic;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-regular.woff2') format('woff2'), url('/fonts/suisseintl-regular.woff') format('woff');
          font-weight: 400;
          font-style: normal;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-regularitalic.woff2') format('woff2'), url('/fonts/suisseintl-regularitalic.woff') format('woff');
          font-weight: 400;
          font-style: italic;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-light.woff2') format('woff2'), url('/fonts/suisseintl-light.woff') format('woff');
          font-weight: 300;
          font-style: normal;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-lightitalic.woff2') format('woff2'), url('/fonts/suisseintl-lightitalic.woff') format('woff');
          font-weight: 300;
          font-style: italic;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-ultralight.woff2') format('woff2'), url('/fonts/suisseintl-ultralight.woff') format('woff');
          font-weight: 200;
          font-style: normal;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-ultralightitalic.woff2') format('woff2'), url('/fonts/suisseintl-ultralightitalic.woff') format('woff');
          font-weight: 200;
          font-style: italic;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-thin.woff2') format('woff2'), url('/fonts/suisseintl-thin.woff') format('woff');
          font-weight: 100;
          font-style: normal;
          font-display: swap;
      }

      @font-face {
          font-family: 'Suisse Intl';
          src: url('/fonts/suisseintl-thinitalic.woff2') format('woff2'), url('/fonts/suisseintl-thinitalic.woff') format('woff');
          font-weight: 100;
          font-style: italic;
          font-display: swap;
      }
      `,
    },
  }
}
