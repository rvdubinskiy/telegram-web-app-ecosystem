import { Stack } from '@mui/material';
import { useRouter } from 'next/navigation';
import { useState } from 'react';

import { useForceExpand } from '../../hooks/useForceExpand';
import { BackButton } from '../BackButton';

import { useWebApp } from '@/core';

export const EarnPage = () => {
  const router = useRouter();
  const globalWebApp = useWebApp();

  useForceExpand();

  return (
    <Stack
      sx={{
        backgroundColor: '#000',
        maxWidth: '100vw',
        height: '100%',
      }}>
      <BackButton
        onClick={() => {
          router.back();
          globalWebApp?.BackButton?.hide();
        }}
      />
    </Stack>
  );
};
