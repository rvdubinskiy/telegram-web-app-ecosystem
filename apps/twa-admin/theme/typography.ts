// ----------------------------------------------------------------------

export function remToPx(value: string) {
  return Math.round(parseFloat(value) * 16)
}

export function pxToRem(value: number) {
  return `${value / 16}rem`
}

export function responsiveFontSizes({sm, md, lg}: {lg: number; md: number; sm: number}) {
  return {
    '@media (min-width:600px)': {
      fontSize: pxToRem(sm),
    },
    '@media (min-width:900px)': {
      fontSize: pxToRem(md),
    },
    '@media (min-width:1200px)': {
      fontSize: pxToRem(lg),
    },
  }
}

declare module '@mui/material/styles' {
  interface TypographyVariants {
    fontSecondaryFamily: React.CSSProperties['fontFamily']
    fontWeightSemiBold: React.CSSProperties['fontWeight']
  }
}

// ----------------------------------------------------------------------

// LEARN MORE
// https://nextjs.org/docs/basic-features/font-optimization#google-fonts

const fontWeights = {
  fontWeightRegular: 400,
  fontWeightMedium: 500,
  fontWeightSemiBold: 600,
  fontWeightBold: 700,
}

export const typography = {
  fontFamily: 'Suisse Intl, Arial, sans-serif',
  ...fontWeights,
  h1: {
    fontWeight: fontWeights.fontWeightRegular,
    lineHeight: 70 / 52,
    fontSize: pxToRem(52),
  },
  h2: {
    fontWeight: fontWeights.fontWeightRegular,
    lineHeight: 36 / 32,
    fontSize: pxToRem(32),
    '@media (min-width: 1024px)': {
      fontWeight: fontWeights.fontWeightRegular,
      lineHeight: 44 / 40,
      fontSize: pxToRem(40),
      letterSpacing: '-0.04em',
    },
  },
  h3: {
    fontWeight: fontWeights.fontWeightRegular,
    lineHeight: 28 / 24,
    fontSize: pxToRem(24),
    '@media (min-width: 1024px)': {
      lineHeight: 36 / 32,
      fontSize: pxToRem(32),
    },
  },
  h4: {
    fontWeight: fontWeights.fontWeightRegular,
    lineHeight: 28 / 24,
    fontSize: pxToRem(24),
  },
  h5: {
    fontWeight: fontWeights.fontWeightRegular,
    lineHeight: 24 / 20,
    fontSize: pxToRem(20),
  },
  h6: {
    fontWeight: fontWeights.fontWeightRegular,
    lineHeight: 28 / 18,
    fontSize: pxToRem(18),
  },
  subtitle1: {
    fontWeight: fontWeights.fontWeightRegular,
    lineHeight: 20 / 16,
    fontSize: pxToRem(16),
  },
  subtitle2: {
    fontWeight: fontWeights.fontWeightRegular,
    lineHeight: 18 / 14,
    fontSize: pxToRem(14),
  },
  body1: {
    fontWeight: fontWeights.fontWeightRegular,
    lineHeight: 20 / 16,
    fontSize: pxToRem(16),
  },
  body2: {
    fontWeight: fontWeights.fontWeightRegular,
    lineHeight: 18 / 14,
    fontSize: pxToRem(14),
  },
  caption: {
    fontWeight: fontWeights.fontWeightRegular,
    lineHeight: 'auto',
    fontSize: pxToRem(12),
  },
  overline: {
    fontWeight: fontWeights.fontWeightRegular,
    lineHeight: 'auto',
    fontSize: pxToRem(12),
    textTransform: 'uppercase',
  },
  platformMenu: {
    fontSize: pxToRem(10),
    lineHeight: 12 / 10,
  },
  button: {
    fontWeight: 400,
    lineHeight: 24 / 14,
    fontSize: pxToRem(14),
    textTransform: 'none',
  },
} as const
