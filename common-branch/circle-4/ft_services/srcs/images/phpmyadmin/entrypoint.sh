#!/bin/sh

DOCKER_ENTRYPOINT=/docker-entrypoint.sh
TEMP="$DOCKER_ENTRYPOINT-temp"

head -n -1 $DOCKER_ENTRYPOINT > $TEMP ; mv $TEMP $DOCKER_ENTRYPOINT ; chmod 775 $DOCKER_ENTRYPOINT

$DOCKER_ENTRYPOINT php-fpm

/usr/sbin/nginx && /usr/local/sbin/php-fpm


