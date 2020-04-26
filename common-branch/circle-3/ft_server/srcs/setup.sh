# Installation of needed services
apt-get install -y wget
apt-get install -y php-mysql
apt-get install -y libnss3-tools
apt install -y php-{zip,mbstring,fpm,gd,xml,cgi,cli,gettext,pear}

# Setting up nginx configuration
mv ./nginx.conf /etc/nginx/sites-available/monsite
ln -s /etc/nginx/sites-available/monsite /etc/nginx/sites-enabled/

# Setting up site directory && index.php
mkdir -p /var/www/monsite
mv ./index.php /var/www/monsite/

# Configuring mysql
service mysql start
echo "CREATE DATABASE wordpress;" | mysql -u root
echo "GRANT ALL PRIVILEGES ON wordpress.* TO 'root'@'localhost';" | mysql -u root
echo "FLUSH PRIVILEGES;" | mysql -u root
echo "update mysql.user set plugin = 'mysql_native_password' where user='root';" | mysql -u root

# Installation of wordpress
mv ./wordpress.tar.gz /var/www/monsite/
cd /var/www/monsite/
tar -xf wordpress.tar.gz
rm wordpress.tar.gz

# Installation of phpmyadmin
wget https://files.phpmyadmin.net/phpMyAdmin/4.9.0.1/phpMyAdmin-4.9.0.1-english.tar.gz
mkdir /var/www/monsite/phpmyadmin
tar -xzf phpMyAdmin-4.9.0.1-english.tar.gz --strip-components=1 -C /var/www/monsite/phpmyadmin
cp /config.inc.php /var/www/monsite/phpmyadmin/

#Creating SSL local certificate
mkdir -p /root/mkcert
cd /root/mkcert
wget https://github.com/FiloSottile/mkcert/releases/download/v1.4.1/mkcert-v1.4.1-linux-amd64
mv mkcert-v1.4.1-linux-amd64 mkcert
chmod +x mkcert
./mkcert -install
./mkcert monsite

# Setting up permissions
chown -R www-data:www-data /var/www/*
chmod -R 755 /var/www/*

# Restarting services
/etc/init.d/php7.3-fpm start
service nginx restart
service mysql restart


