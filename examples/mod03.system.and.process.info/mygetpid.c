#include <unistd.h>
#include <stdio.h>

main() {

  printf("My pid is: %d\n", getpid());
  printf("My parent pid is: %d\n", getppid());
}
