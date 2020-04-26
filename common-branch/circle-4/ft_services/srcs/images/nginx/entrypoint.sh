#!bin/sh

rc-update add sshd && rc-status\
    && mkdir -p /run/openrc/softlevel && /etc/init.d/sshd start\
    && /etc/init.d/sshd restart

SSH_USER=${SSH_USER:-"undefined"}
SSH_PASSWORD=${SSH_PASSWORD:-"undefined"}
HOME="/home/${SSH_USER}"


adduser --disabled-password $SSH_USER

echo "$SSH_USER:$SSH_PASSWORD" | chpasswd

/usr/sbin/nginx -g 'daemon off;'
