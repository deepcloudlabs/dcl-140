#include <sys/unistd.h>
#include <stdio.h>

main() {

  printf("Number of processors: %d\n", sysconf(_SC_NPROCESSORS_CONF));
  printf("Memory page size: %d\n", sysconf(_SC_PAGESIZE));
  printf("Clock ticks/second: %d\n", sysconf(_SC_CLK_TCK));
  printf("Number of files that can be opened: %d\n", sysconf(_SC_OPEN_MAX));
}
