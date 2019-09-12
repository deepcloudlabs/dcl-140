#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

main() {
  printf("My uid is %d\n", getuid() );
}
