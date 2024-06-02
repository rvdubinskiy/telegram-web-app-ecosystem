import { MutableRefObject, useContext, useEffect } from 'react';

import { optionsContext } from './context';

const _noop = () => {};

const useSmoothButtonsTransition = ({
  id,
  show = _noop,
  hide = _noop,
  currentShowedIdRef,
}: {
  id: string;
  show: typeof _noop | undefined;
  hide: typeof _noop | undefined;
  currentShowedIdRef: MutableRefObject<string | null>;
}) => {
  const { smoothButtonsTransition, smoothButtonsTransitionMs } = useContext(optionsContext);

  useEffect(() => {
    show();
    currentShowedIdRef.current = id;
  }, [hide, id, currentShowedIdRef, show, smoothButtonsTransition, smoothButtonsTransitionMs]);
};

export default useSmoothButtonsTransition;
