FROM nginx:alpine

RUN apk add openssh && apk add openrc

COPY  ./sshd_config /etc/ssh/sshd_config

COPY ./entrypoint.sh /entrypoint.sh

ENTRYPOINT [ "sh",  "entrypoint.sh" ]

EXPOSE 31111 80 443
