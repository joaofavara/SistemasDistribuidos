#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigcatcher() {
  printf("O processo %d captou um sinal\n", getpid());
  signal(SIGINT, sigcatcher);
}

int main () {
  int ppid;

  signal(SIGINT, sigcatcher);

  if (fork() == 0) {
    printf("O processo filho %d vai executar\n", ppid=getpid());
    if (kill(ppid, SIGINT) == -1)
      exit(1);
  }
  else {
    sleep(10);
    printf("O processo pai vai executar\n");
  }
}