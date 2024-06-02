import type { BreakpointsOptions } from '@mui/material';

declare module '@mui/material/styles' {
  interface BreakpointOverrides {
    xxl: true;
  }
}

export const breakpoints: BreakpointsOptions = {
  values: {
    xs: 0,
    sm: 429,
    md: 1024,
    lg: 1280,
    xl: 1440,
    xxl: 1920,
  },
};
