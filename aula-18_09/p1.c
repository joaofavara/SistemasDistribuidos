#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <signal.h>

struct tms pb1, pb2;
clock_t pt1, pt2;


// int main() {
//   int status;

//   if (fork() == 0) {
//     int aux = 0;
//     while(aux <= 1000) {
//       sleep(2);
//       printf("O processo filho1 %d vai executar\n", getpid());
//     }
//   }
//   if (fork() == 0) {
//       int aux = 0;
//       while(aux <= 1000) {
//         sleep(5);
//         printf("O processo filho2 %d vai executar\n", getpid());
//       }
//   }
//   else {
//     printf("O processo pai %d vai executar\n", getpid());
//     wait(&status);
//     printf("o processo pai %d terminou\n", getpid());
//   }
// }


void f2() {
  printf("FILHO %d: capitei o sinal\n", getpid());

  pt2 = times(&pb2);
  printf("Tempo de execucao: %.2f\n", (float) (pt2-pt1)/100);
  printf("Execucao: %u - user %u - kernel %u\n\n", pt2-pt1, pb2.tms_utime-pb1.tms_utime, pb2.tms_stime-pb1.tms_stime);
  
  signal(SIGALRM, f2);
  alarm(2);
}

void f5() {
  printf("PAI %d: capitei o sinal\n", getpid());
  signal(SIGALRM, f5);
  alarm(5);
}

int main() {
  if(fork() == -0) {
    signal(SIGALRM, f2);
    alarm(2);
    for(;;);
  } else {
    signal(SIGALRM, f5);
    alarm(5);
    for(;;);
  }
}