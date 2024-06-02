import type { NextPage } from 'next';
import Head from 'next/head';

import { MainPage } from '../features/MainPage/MainPage';

const Home: NextPage = () => {
  return (
    <>
      <Head>
        <title>Next.js + Tailwind CSS + Telegram&apos;s Web App</title>
        <link rel="icon" href="/favicon.ico" />
      </Head>

      <MainPage />
    </>
  );
};

export default Home;
