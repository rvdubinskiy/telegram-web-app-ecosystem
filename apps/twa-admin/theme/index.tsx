'use client';

import type { PaletteMode } from '@mui/material';
import CssBaseline from '@mui/material/CssBaseline';
import { ThemeProvider as MuiThemeProvider, createTheme } from '@mui/material/styles';
import type { Direction, ThemeOptions } from '@mui/material/styles';
import merge from 'lodash/merge';
import { useMemo } from 'react';

import { customShadows } from './customShadows';
import { GlobalStyles } from './globalStyles';
import NextAppDirEmotionCacheProvider from './next-emotion-cache';
import { createContrast } from './options/contrast';
import type { PresetType } from './options/presets';
import { createPresets } from './options/presets';
// options
import { componentsOverrides } from './overrides';
// system
import { palette } from './palette';
import { shadows } from './shadows';
import { typography } from './typography';

// ----------------------------------------------------------------------

interface Props {
  children: React.ReactNode;
}

interface ThemeSettings {
  colorPreset: PresetType;
  contrast: 'bold' | 'default';
  direction: Direction;
  mode: PaletteMode;
}

const themeSettings: ThemeSettings = {
  mode: 'light',
  direction: 'ltr',
  contrast: 'bold',
  colorPreset: 'blue',
};

export default function ThemeProvider({ children }: Props) {
  const presets = createPresets(themeSettings.colorPreset);

  const contrast = createContrast(themeSettings.contrast, themeSettings.mode);

  const memoizedValue = useMemo(
    () => ({
      palette: {
        ...palette(themeSettings.mode),
        ...presets.palette,
        ...contrast.palette,
      },
      customShadows: {
        ...customShadows(themeSettings.mode),
        ...presets.customShadows,
      },
      direction: themeSettings.direction,
      shadows: shadows(themeSettings.mode),
      shape: { borderRadius: 8 },
      typography,
    }),
    [
      themeSettings.mode,
      themeSettings.direction,
      presets.palette,
      presets.customShadows,
      contrast.palette,
    ]
  );

  const theme = createTheme(memoizedValue as ThemeOptions);

  theme.components = merge(componentsOverrides(theme), contrast.components);

  const themeWithLocale = useMemo(() => createTheme(theme), [theme]);

  return (
    <NextAppDirEmotionCacheProvider options={{ key: 'css' }}>
      <MuiThemeProvider theme={themeWithLocale}>
        <CssBaseline />
        <GlobalStyles />
        {children}
      </MuiThemeProvider>
    </NextAppDirEmotionCacheProvider>
  );
}
