#!bin/sh

FTPS_USER=${FTPS_USER:-"undefined"}
FTPS_PASSWORD=${FTPS_PASSWORD:-"undefined"}

adduser --disabled-password $FTPS_USER

echo "$FTPS_USER:$FTPS_PASSWORD" | chpasswd


/usr/sbin/vsftpd /etc/vsftpd/vsftpd.conf
