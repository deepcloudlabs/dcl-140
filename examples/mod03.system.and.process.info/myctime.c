#include <sys/types.h>
#include <time.h>
#include <stdio.h>

main() {

  time_t t;

  time(&t);
  printf("%s", ctime(&t));
}
