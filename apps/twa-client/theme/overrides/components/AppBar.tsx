import type {Theme} from '@mui/material/styles'

// ----------------------------------------------------------------------

export function AppBar(theme: Theme) {
  return {
    MuiAppBar: {
      styleOverrides: {
        root: {
          boxShadow: 'none',
        },
      },
    },
  }
}
