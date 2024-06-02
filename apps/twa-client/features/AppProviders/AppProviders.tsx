import { QueryClient, QueryClientProvider } from '@tanstack/react-query';

import { ProtectedLayout } from '../ProtectedLayout';

const queryClient = new QueryClient({
  defaultOptions: {
    queries: {
      retry: false,
    },
    mutations: {
      retry: false,
    },
  },
});

interface AppProvidersProps {}

export function AppProviders({ children }: React.PropsWithChildren<AppProvidersProps>) {
  return (
    <QueryClientProvider client={queryClient}>
      <ProtectedLayout>{children}</ProtectedLayout>
    </QueryClientProvider>
  );
}
