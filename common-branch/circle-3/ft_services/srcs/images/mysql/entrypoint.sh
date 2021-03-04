#!/bin/sh

mysql_install_db --user=root > /dev/null

mkdir -p /run/mysqld

TEMP_FILE=`mktemp`

cat << EOF > $TEMP_FILE
FLUSH PRIVILEGES;
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY "$MYSQL_ROOT_PASS" WITH GRANT OPTION;
EOF

/usr/bin/mysqld --user=root --bootstrap --verbose=0 < $TEMP_FILE

rm -f $TEMP_FILE

/usr/bin/mysqld --user=root --console
