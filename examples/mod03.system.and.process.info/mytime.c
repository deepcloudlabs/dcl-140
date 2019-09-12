#include <sys/types.h>
#include <time.h>
#include <stdio.h>

main() {

  time_t t;

  time(&t);
  printf("Time in seconds = %d\n", t);
}
