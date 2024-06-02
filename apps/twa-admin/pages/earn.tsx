import type { NextPage } from 'next';
import Head from 'next/head';

import { EarnPage } from '../features/EarnPage';

const EarnRoot: NextPage = () => {
  return (
    <>
      <Head>
        <title>Next.js + Tailwind CSS + Telegram&apos;s Web App</title>
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <EarnPage />
    </>
  );
};

export default EarnRoot;
