import { DispatchWithoutAction, useCallback, useEffect, useState } from 'react';

import { useWebApp } from '../core';

/**
 * This hook provided isExpanded state, and expand() handle
 * You have to look original description in {@link telegram!WebApp} for more information
 *
 * `isExpanded` can be `undefined`
 *
 * ```tsx
 * import { useForceExpand } from "../useForceExpand";
 *
 * useForceExpand();
 * ```
 *
 * @privateRemarks
 * Api doesn't provide event for listening isExpanded, so we use
 * viewportChanged, but it is an unsafe way
 *
 * @group Hooks
 */
export const useForceExpand = () => {
  const WebApp = useWebApp();

  useEffect(() => {
    if (!WebApp || WebApp.isExpanded) return;

    WebApp.expand();
  }, [WebApp]);
};
