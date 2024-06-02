import { Icon } from '@iconify/react';
import Box from '@mui/material/Box';
import type { BoxProps } from '@mui/material/Box';
import { forwardRef } from 'react';

import type { IconifyProps } from './types';

// ----------------------------------------------------------------------

interface Props extends BoxProps {
  icon: IconifyProps;
}

const Iconify = forwardRef<SVGElement, Props>(({ icon, width = 20, sx, ...other }, ref) => (
  <Box
    className="component-iconify"
    component={Icon}
    icon={icon}
    ref={ref}
    sx={{ width, height: width, ...sx }}
    {...other}
  />
));

export default Iconify;
