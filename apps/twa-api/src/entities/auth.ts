import { InitDataUnsafe } from '@twa/entities/src/webapp/types';

export interface UserData {
  userId: number;
  webAppData: InitDataUnsafe;
}

export type DecodedUserData = UserData & { exp: number; jti: string };
