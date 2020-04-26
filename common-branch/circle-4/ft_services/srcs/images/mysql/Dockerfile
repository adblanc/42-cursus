FROM alpine

RUN apk update && apk add mysql mysql-client && mkdir /app

COPY entrypoint.sh /entrypoint.sh
COPY mysql.cnf /etc/mysql/my.cnf

ENTRYPOINT [ "sh", "/entrypoint.sh" ]
