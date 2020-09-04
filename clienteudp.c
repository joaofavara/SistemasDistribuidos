#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>

#define DATA "Esta eh a mensagem que quero enviar"

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
	int sock;
  struct mensagem msg;
  int count, tam;
	struct sockaddr_in name;
	struct hostent *hp, *gethostbyname();

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
  hp = gethostbyname(argv[1]);
  if (hp==0) {
      fprintf(stderr, "%s: unknown host ", argv[1]);
      exit(2);
  }
  bcopy ((char *)hp->h_addr, (char *)&name.sin_addr, hp->h_length);
	name.sin_family = AF_INET;
	name.sin_port = htons(atoi(argv[2]));
  
	/* Envia */
  msg.codigo=1;
	if (sendto (sock,(char *)&msg,sizeof (struct mensagem), 0, (struct sockaddr *)&name, sizeof name)<0)
                perror("sending datagram message");
  
  if (recvfrom(sock, (char *)&msg, sizeof(msg), 0, (struct sockaddr *)&name, &tam)) {
    printf("count - cliente: %i\n", msg.resposta);
  }
}
