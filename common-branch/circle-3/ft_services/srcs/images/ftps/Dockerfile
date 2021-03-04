FROM alpine

RUN apk update \
    && apk add vsftpd

COPY vsftpd.pem /etc/vsftpd/cert/vsftpd.pem
COPY entrypoint.sh /var/lib/entrypoint.sh
COPY vsftpd.conf /etc/vsftpd/vsftpd.conf

EXPOSE 21 20 10090 10091 10092 10093 10094 10095 10096 10097 10098 10099 10100

ENTRYPOINT ["sh", "/var/lib/entrypoint.sh"]
