import { useMutation } from '@tanstack/react-query';

import { SigninData, authSigninHandler } from '../handlers/auth/authSignin';

import useWebApp from '@/hooks/useWebApp';

export const useAuth = () => {
  const webAppContext = useWebApp();
  const signinMutation = useMutation({ mutationFn: authSigninHandler });

  const signin = async (initData: SigninData) => {
    try {
      const data = await signinMutation.mutateAsync(
        initData ?? {
          initData: webAppContext,
        }
      );
      sessionStorage.setItem('accessToken', data.accessToken);
      sessionStorage.setItem('refreshToken', data.refreshToken);

      return data;
    } catch (error) {
      console.error(error);
    }

    return null;
  };

  return { signin, ...signinMutation };
};
