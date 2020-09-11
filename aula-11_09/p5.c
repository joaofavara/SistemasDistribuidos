#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main (argc, argv)
  int argc;
  char *argv[];
{
  int i, ret_val, ret_code;

  if (argc > 1)
    signal(SIGCLD, SIG_IGN);
  
  for(int i = 0; i < 15; i++) {
    if(fork() == 0) {
      printf("Sou o processo filho %d\n", getpid());
      exit(i);
    }

    ret_val = wait(&ret_code);
    printf("retval: %d  retcode: %d\n", ret_val, ret_code);
  }

}