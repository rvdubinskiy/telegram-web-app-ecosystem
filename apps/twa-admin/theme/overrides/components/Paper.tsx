import {alpha} from '@mui/material/styles'

import type {Theme} from '@mui/material/styles'

// ----------------------------------------------------------------------

export function Paper(theme: Theme) {
  return {
    MuiPaper: {
      styleOverrides: {
        root: {
          backgroundImage: 'none',
        },
        outlined: {
          borderColor: alpha(theme.palette.grey[500], 0.16),
        },
      },
    },
  }
}
