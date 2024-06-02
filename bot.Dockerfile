# ---- Build Stage ----
FROM node:18-alpine AS base
FROM base AS build

WORKDIR /app

RUN npm install -g pnpm

COPY pnpm-workspace.yaml pnpm-workspace.yaml
COPY package.json package.json
COPY apps/twa-bot apps/twa-bot 
COPY packages packages

WORKDIR /app/apps/twa-bot
RUN pnpm install
RUN pnpm run build
RUN pnpm install --production

# ---- Production Stage ----
FROM base AS production

WORKDIR /app/apps/twa-bot

COPY --from=build /app/apps/twa-bot/node_modules ./node_modules
COPY --from=build /app/apps/twa-bot/package.json ./package.json
COPY --from=build /app/apps/twa-bot/build ./build

EXPOSE 3020

CMD [ "node", "build/index.js" ]
