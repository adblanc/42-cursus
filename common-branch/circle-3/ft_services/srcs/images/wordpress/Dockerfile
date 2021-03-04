FROM wordpress:php7.4-fpm-alpine

RUN apk update && apk add mysql-client nginx 

COPY nginx.conf /etc/nginx/nginx.conf
COPY entrypoint.sh /entrypoint.sh
COPY wordpress-database.sql /wordpress-database.sql

ENTRYPOINT ["sh", "/entrypoint.sh"]
