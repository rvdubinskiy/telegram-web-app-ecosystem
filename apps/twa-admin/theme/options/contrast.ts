import {customShadows} from '../customShadows'
import {grey} from '../palette'

// ----------------------------------------------------------------------

export function createContrast(contrast: 'bold' | 'default', mode: 'dark' | 'light') {
  const theme = {
    ...(contrast === 'bold' &&
      mode === 'light' && {
        palette: {
          background: {
            default: grey[200],
          },
        },
      }),
  }

  const components = {
    ...(contrast === 'bold' && {
      MuiCard: {
        styleOverrides: {
          root: {
            boxShadow: customShadows(mode).z1,
          },
        },
      },
    }),
  }

  return {
    ...theme,
    components,
  }
}
