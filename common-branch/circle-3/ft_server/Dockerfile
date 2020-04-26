FROM debian:buster

RUN \
	apt-get update && \
	apt-get upgrade -y && \
	apt-get install -y mariadb-server && \
	apt-get install -y nginx

COPY ./srcs/nginx.conf ./
COPY ./srcs/setup.sh ./
COPY ./srcs/index.php ./
COPY ./srcs/wordpress.tar.gz ./
COPY ./srcs/config.inc.php ./

CMD bash ./setup.sh && tail -f /dev/null
