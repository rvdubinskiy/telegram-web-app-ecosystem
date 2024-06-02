/**
 * {@link telegram!WebAppChat}
 */
export type WebAppChat = {
  id: number;
  type: 'group' | 'supergroup' | 'channel';
  title: string;
  username?: string;
  photo_url?: string;
};

/**
 * {@link telegram!WebAppUser}
 */
export type WebAppUser = {
  id: number;
  is_bot?: boolean;
  first_name: string;
  last_name?: string;
  username?: string;
  language_code?: string;
  photo_url?: true;
  added_to_attachment_menu?: true;
  allows_write_to_pm?: true;
};

export type InitData = string;

/**
 * {@link telegram!WebAppInitData}
 */
export type InitDataUnsafe = {
  query_id?: string;
  user?: WebAppUser;
  receiver?: WebAppUser;
  chat_type?: 'sender' | 'private' | 'group' | 'supergroup' | 'channel';
  chat_instance?: string;
  start_param?: string;
  auth_date: number;
  hash: string;
  chat?: WebAppChat;
  can_send_after?: number;
};
