MYSQL="mysql -h $WORDPRESS_DB_HOST -u $WORDPRESS_DB_USER --password=$WORDPRESS_DB_PASSWORD"

DOCKER_ENTRYPOINT=/usr/local/bin/docker-entrypoint.sh
TEMP="$DOCKER_ENTRYPOINT-temp"

$MYSQL -e '' || exit 1

if ! $MYSQL -e 'USE wordpress;'
    then
	$MYSQL -e 'CREATE DATABASE wordpress;' ||
		( $MYSQL -e 'DROP DATABASE wordpress;'; exit 1)
    $MYSQL wordpress < /wordpress-database.sql ||
		( $MYSQL -e 'DROP DATABASE wordpress;'; exit 1)
fi

head -n -1 $DOCKER_ENTRYPOINT > $TEMP ; mv $TEMP $DOCKER_ENTRYPOINT ; chmod 775 $DOCKER_ENTRYPOINT

$DOCKER_ENTRYPOINT php-fpm

/usr/sbin/nginx && /usr/local/sbin/php-fpm 
