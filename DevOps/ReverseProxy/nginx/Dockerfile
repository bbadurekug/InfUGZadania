FROM alpine:latest AS build

WORKDIR /app

COPY ./app/frontend .


FROM nginx:1.27-alpine

RUN rm /etc/nginx/conf.d/default.conf

COPY ./nginx/default.conf /etc/nginx/conf.d/default.conf

COPY --from=build /app /usr/share/nginx/html

EXPOSE 80