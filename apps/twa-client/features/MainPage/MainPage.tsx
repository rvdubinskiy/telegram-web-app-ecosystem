import { Box, Stack, Typography } from '@mui/material';
import { useTransition, animated, useSpringValue, useSpring } from '@react-spring/web';
import { useRouter } from 'next/navigation';
import { FC, memo, useEffect, useRef, useState } from 'react';

import { useForceExpand } from '../../hooks/useForceExpand';
import useHapticFeedback from '../../hooks/useHapticFeedback';
import useShowPopup from '../../hooks/useShowPopup';
import { BackButton } from '../BackButton';
import { MainButton, MainButtonProps } from '../MainButton';

import { useWebApp } from '@/core';
import useThemeParams from '@/hooks/useThemeParams';

interface CoinType {
  key: string;
}

// eslint-disable-next-line react/display-name
const Coin = ({ coords, offset }: { coords: any; offset: number; id: number }) => {
  const boxRef = useRef<HTMLDivElement | null>(null);
  const timer = useRef<ReturnType<typeof requestAnimationFrame>>();

  useEffect(() => {
    const baseCoords = {
      startX: coords.x,
      startY: coords.y - offset,
      endX: coords.x,
      endY: coords.yq - 250,
    };

    let opacityValue = 1;
    let endValue = 1;

    function updatePosition() {
      if (endValue < 250) {
        opacityValue -= 0.01;
        endValue += 2;
        const currentX = baseCoords.startX;
        const currentY = baseCoords.startY - endValue;

        boxRef.current?.style.setProperty(
          'transform',
          `translate3d(${currentX}px, ${currentY}px, 0)`
        );
        boxRef.current?.style.setProperty('opacity', String(Math.max(opacityValue, 0)));

        timer.current = requestAnimationFrame(updatePosition);
      } else {
        boxRef.current?.style.setProperty(
          'transform',
          `translate3d(${baseCoords.endX}px, ${baseCoords.endY}px, 0)`
        );
        boxRef.current?.style.setProperty('opacity', '0');
      }
    }

    timer.current = requestAnimationFrame(updatePosition);

    return () => clearTimeout(timer.current);
  }, []);
  return (
    <Box ref={boxRef} position="absolute" sx={{ zIndex: 0 }}>
      <Typography fontSize="32px" color="white" fontWeight={500}>
        1
      </Typography>
    </Box>
  );
};

export const MainPage = () => {
  const [buttonState, setButtonState] = useState<
    object & Pick<MainButtonProps, 'text' | 'progress' | 'disable'>
  >({
    text: 'BUTTON TEXT',
    progress: false,
    disable: false,
  });

  const [impactOccurred, notificationOccurred, selectionChanged] = useHapticFeedback();
  const containerRef = useRef<HTMLDivElement | null>(null);
  const START_COIN_AMOUNT = 30_000;
  const [coinsCount, setCoinsCount] = useState(START_COIN_AMOUNT);
  const router = useRouter();
  const globalWebApp = useWebApp();

  const [divs, setDivs] = useState<any[]>([]);
  const timer = useRef<ReturnType<typeof setTimeout>>();

  const onMineCoin = (e) => {
    if (containerRef.current === null || !containerRef.current?.contains(e.target)) {
      return;
    }

    for (const touch of e.changedTouches) {
      const { top } = containerRef.current.getBoundingClientRect();
      const newDiv = {
        id: Math.random(), // Уникальный идентификатор для ключа
        startX: touch.clientX,
        startY: touch.clientY,
        offset: top,
      };
      setDivs((currentDivs) => [...currentDivs, newDiv]);
      setCoinsCount((c) => ++c);
      impactOccurred('soft');

      // Удаляем div через 5 секунд
      timer.current = setTimeout(() => {
        setDivs((currentDivs) => currentDivs.filter((div) => div.id !== newDiv.id));
      }, 1500);
    }
  };

  useForceExpand();

  useEffect(() => {
    return () => {
      clearTimeout(timer.current);
    };
  }, []);

  return (
    <Stack
      sx={{
        backgroundColor: '#000',
        maxWidth: '100vw',
        height: '100%',
      }}>
      <Stack />
      <Stack
        alignItems="center"
        sx={{
          padding: '24px 0',
        }}>
        <Typography variant="h2" color="white">
          {coinsCount}
        </Typography>
      </Stack>
      <Stack
        ref={containerRef}
        sx={{
          userSelect: 'none',
          padding: '12px 0',
        }}
        alignItems="center"
        justifyContent="center"
        onTouchStart={onMineCoin}
        position="relative"
        zIndex={1}>
        <img
          style={{
            borderRadius: '50%',
          }}
          src="https://e7.pngegg.com/pngimages/763/672/png-clipart-cookie-clicker-clicker-heroes-incremental-game-cookie-game-baked-goods-thumbnail.png"
        />
        <Box
          zIndex={0}
          sx={{
            top: 0,
            left: 0,
            width: '100%',
            height: '100%',
            position: 'absolute',
          }}>
          {divs.map((div) => (
            <Coin
              key={div.id}
              id={div.id}
              offset={div.offset}
              coords={{
                x: div.startX,
                y: div.startY,
              }}
            />
          ))}
        </Box>
      </Stack>
      {/* <BackButton
        onClick={() => {
          showPopup({
            message: 'back button click',
          });
        }}
      /> */}
      <MainButton
        {...buttonState}
        onClick={() => {
          impactOccurred('light');
          notificationOccurred('success');
          globalWebApp?.MainButton.hide();
          router.push('/earn');
        }}
      />
    </Stack>
  );
};
