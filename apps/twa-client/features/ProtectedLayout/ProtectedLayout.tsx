import { useEffect, useState, FC, ReactNode } from 'react';

import { useAuth } from '@/api/hooks/useAuth';

interface ProtectedLayoutProps {
  children?: ReactNode;
}

export const ProtectedLayout: FC<ProtectedLayoutProps> = ({ children }) => {
  const [isHashValid, setIsHashValid] = useState(false);
  const { signin } = useAuth();

  // Wait for validation to complete before rendering the page and stop the
  // rendering if the hash is invalid. Comment out the following useEffect
  // hook to see the page render without the hash validation.
  useEffect(() => {
    window?.Telegram?.WebApp?.setHeaderColor?.('#000000');
    window?.Telegram?.WebApp?.setBackgroundColor?.('#000000');

    if (!sessionStorage.getItem('accessToken')) {
      signin({
        initData: window.Telegram?.WebApp.initDataUnsafe,
      }).then((response) => {
        setIsHashValid(Boolean(response?.accessToken));
      });
    }
    // axios
    //   .post('/api/validate-hash', {
    //     hash: window.Telegram?.WebApp.initDataUnsafe,
    //   })
    //   .then((response) => setIsHashValid(response.status === 200));
  }, []);

  if (!isHashValid) {
    return null;
  }

  return <>{children}</>;
};
