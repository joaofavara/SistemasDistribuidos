#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigcatcher() {
  static int count = 1;
  printf("O processo %d captou um sinal (%d)\n", getpid(), count++);
  // signal(SIGINT, sigcatcher);
}

int main () {
  int i, j , ppid, x = 10;

  signal(SIGINT, sigcatcher);

  if (fork() == 0) {
    sleep(5);
    ppid=getpid();
    for(;;)
      if (kill(ppid, SIGINT) == -1)
        printf("O processo pai %d ja terminou\n", ppid);
        exit(-1);
  }
  else {
    nice(10);
    for(i = 0; i < 40000; i++) {
      for(j = 0; j < 40000; i++) {
        x=(3+7*x)%1000;
      }
    }
  }
}