#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sigcatcher() {
  printf("Peguei um sinal SIGCLD\n");
  signal(SIGCLD, sigcatcher);
}

int main () {
  int i, j , ppid, x = 10;

  signal(SIGCLD, sigcatcher);

  if (fork() == 0) {
    sleep(5);
    printf("O processo filho %d vai terminar\n", getpid()); 
  }
  else {
    pause();
  }
}