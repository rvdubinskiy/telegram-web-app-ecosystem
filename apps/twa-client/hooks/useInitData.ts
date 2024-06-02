import { InitDataUnsafe, InitData } from '@twa/entities/src/webapp/types';

import { useWebApp } from '../core';

/**
 * This hook provides `initDataUnsafe` and `initData`
 * You have to look original description in {@link telegram!WebApp}, because hook just return this.
 *
 * ```tsx
 * import { useInitData } from "@vkruglikov/react-telegram-web-app";
 *
 * const [initDataUnsafe] = useInitData();
 * const [initDataUnsafe, initData] = useInitData();
 *
 * ```
 * @group Hooks
 */
const useInitData = (): readonly [InitDataUnsafe | undefined, InitData | undefined] => {
  const WebApp = useWebApp();

  return [WebApp?.initDataUnsafe, WebApp?.initData] as const;
};

export default useInitData;
