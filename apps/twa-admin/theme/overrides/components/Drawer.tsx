import {drawerClasses} from '@mui/material/Drawer'
import {alpha} from '@mui/material/styles'

import type {DrawerProps} from '@mui/material/Drawer'
import type {Theme} from '@mui/material/styles'

import {paper} from '../../css'

// ----------------------------------------------------------------------

export function Drawer(theme: Theme) {
  const lightMode = theme.palette.mode === 'light'

  return {
    MuiDrawer: {
      styleOverrides: {
        root: ({ownerState}: {ownerState: DrawerProps}) => ({
          ...(ownerState.variant === 'temporary' && {
            [`& .${drawerClasses.paper}`]: {
              ...paper({theme}),
              ...(ownerState.anchor === 'left' && {
                boxShadow: `40px 40px 80px -8px ${alpha(
                  lightMode ? theme.palette.grey[500] : theme.palette.common.black,
                  0.24,
                )}`,
              }),
              ...(ownerState.anchor === 'right' && {
                boxShadow: `-40px 40px 80px -8px ${alpha(
                  lightMode ? theme.palette.grey[500] : theme.palette.common.black,
                  0.24,
                )}`,
              }),
            },
          }),
        }),
      },
    },
  }
}
