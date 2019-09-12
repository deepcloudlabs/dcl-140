#include <sys/types.h>
#include <time.h>
#include <stdio.h>
main() {

  /* Declare a pointer variable only */
  time_t *tptr;

  time(tptr);
  printf("Machine time in seconds = %d\n", *tptr);
}
