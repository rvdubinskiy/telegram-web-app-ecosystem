import type {Theme} from '@mui/material/styles'

import {menuItem} from '../../css'

// ----------------------------------------------------------------------

export function Menu(theme: Theme) {
  return {
    MuiMenuItem: {
      styleOverrides: {
        root: {
          ...menuItem(theme),
        },
      },
    },
  }
}
