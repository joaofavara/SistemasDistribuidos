#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct mensagem {
  int codigo;
  int resposta;
  long ip;
  int port;
};

int main(argc, argv)
     int argc;
     char *argv[];
{
  struct mensagem msg;
	int sock, length;
	struct sockaddr_in name;
	char buf[1024];
  int count = 0;
  
  /* Cria o socket de comunicacao */
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock<0) {
	/*
	/- houve erro na abertura do socket
	*/
		perror("opening datagram socket");
		exit(1);
	}
	/* Associa */
	name.sin_family = AF_INET;
	name.sin_addr.s_addr = INADDR_ANY;
  name.sin_port = htons(2020);
	if (bind(sock,(struct sockaddr *)&name, sizeof name ) < 0) {
		perror("binding datagram socket");
		exit(1);
	}
        /* Imprime o numero da porta */
	length = sizeof(name);
	if (getsockname(sock,(struct sockaddr *)&name, &length) < 0) {
		perror("getting socket name");
		exit(1);
	}
	printf("Socket port #%d\n",ntohs(name.sin_port));

	/* Le */
  while(1) {
    if (recvfrom(sock, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&name, &length))
                  perror("receiving datagram packet");
    printf("\n");
    printf("family: %u\n", name.sin_family);
    printf("port: %d\n", name.sin_port);
    printf("addr: %d\n", name.sin_addr.s_addr);
    printf("addr 2: %s\n", inet_ntoa(name.sin_addr));
    count++;
    msg.resposta=count;

    if (sendto (sock, (char *)&msg, sizeof(struct mensagem), 0, (struct sockaddr *)&name, sizeof name)<0)
            perror("sending datagram message");
  }
}
