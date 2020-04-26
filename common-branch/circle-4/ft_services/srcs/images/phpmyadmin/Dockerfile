FROM phpmyadmin/phpmyadmin:fpm-alpine

RUN apk update && apk add nginx

COPY entrypoint.sh /entrypoint.sh
COPY nginx.conf /etc/nginx/nginx.conf

ENTRYPOINT ["sh", "/entrypoint.sh"]

