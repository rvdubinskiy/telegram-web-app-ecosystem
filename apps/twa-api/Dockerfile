# ---- Build Stage ----
FROM node:18-alpine AS base
FROM base AS build

WORKDIR /app

RUN npm install -g pnpm

COPY . .
RUN pnpm install
RUN pnpm run build
RUN pnpm install --production

# ---- Production Stage ----
FROM base AS production

WORKDIR /app

COPY --from=build /app/node_modules ./node_modules
COPY --from=build /app/package.json ./package.json
COPY --from=build /app/build ./build
COPY --from=build /app/.env.local ./.env.local

EXPOSE 3010

CMD [ "node", "build/server.js" ]
