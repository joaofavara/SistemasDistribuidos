#include <stdio.h>
#include <stdlib.h>

int main () {
  int status;

  if (fork() == 0) {
    printf("O processo filho %d vai executar\n", getpid());
    execl("/bin/date", "date", 0);
  }
  else {
    printf("O processo pai %d vai executar\n", getpid());
    wait(&status);
    printf("o processo pai %d terminou\n", getpid());
  }
}