import type {Theme} from '@mui/material/styles'

// ----------------------------------------------------------------------

export function SvgIcon(theme: Theme) {
  return {
    MuiSvgIcon: {
      styleOverrides: {
        fontSizeLarge: {
          width: 32,
          height: 32,
          fontSize: 'inherit',
        },
      },
    },
  }
}
