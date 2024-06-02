import mongoose from 'mongoose';
const Schema = mongoose.Schema;

const userSchema = new Schema(
  {
    telegram_id: { type: Number, required: true, unique: true },
    first_name: { type: String },
    last_name: { type: String },
    username: { type: String },
    created_at: { type: Date, required: true },
    phone: { type: String },
    photo: { type: String },
    status: { type: String },
    lang_code: { type: String },
    is_premium: { type: Boolean },
    is_bot: { type: Boolean },
    is_subscribed: { type: Boolean },
    invites: { type: Array },
    wallet: {
      type: {
        address: String,
        chain: String,
        walletName: String,
      },
    },
  },
  { timestamps: true }
);

export const User = mongoose.model('User', userSchema);
