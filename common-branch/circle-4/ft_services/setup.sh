
if ! type minikube &> /dev/null; then
	echo 'Error: minikube is not installed. Please install it'
	exit 1
fi

mkdir -p /goinfre/${USER}/{com.docker.docker,.docker}
ln -sf /goinfre/${USER}/com.docker.docker ~/Library/Containers/com.docker.docker
ln -sf /goinfre/${USER}/.docker ~/.docker
#prepare minikube
rm -rf ~/.minikube
mkdir -p /goinfre/${USER}/.minikube
ln -sf /goinfre/${USER}/.minikube ~/.minikube

echo "Starting minikube..."
minikube delete && minikube start --cpus=4 --memory=3000mb --disk-size=10000mb --vm-driver virtualbox
minikube addons enable ingress
minikube addons enable metrics-server

MINI_IP=`minikube ip`

VSFTPD_CONF="srcs/images/ftps/vsftpd.conf"

SQL_DB="srcs/images/wordpress/wordpress.sql"
SQL_DB_COPY="srcs/images/wordpress/wordpress-database.sql"

telegraf="srcs/telegraf-secrets.yaml"

LINE="CLUSTER_IP"

grep -q 'pasv_address' $VSFTPD_CONF && sed -i "" "s/^pasv_address.*/pasv_address=$MINI_IP/" $VSFTPD_CONF || echo "pasv_address=$MINI_IP" >> $VSFTPD_CONF
grep -q $LINE $telegraf && sed -i "" "s/^  $LINE.*/  $LINE: $MINI_IP/" $telegraf || echo "  $LINE: $MINI_IP" >> $telegraf

cp $SQL_DB $SQL_DB_COPY
sed -i "" "s/$LINE/$MINI_IP/g" $SQL_DB_COPY

eval $(minikube docker-env)

docker build -t my-grafana srcs/images/grafana
docker build -t my-ftps srcs/images/ftps
docker build -t my-nginx srcs/images/nginx
docker build -t my-wordpress srcs/images/wordpress
docker build -t my-phpmyadmin srcs/images/phpmyadmin
docker build -t my-mysql srcs/images/mysql

kubectl apply -k srcs 

minikube dashboard

