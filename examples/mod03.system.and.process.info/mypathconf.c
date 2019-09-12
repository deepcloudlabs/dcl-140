#include <unistd.h>
#include <stdio.h>

main() {

  printf("Maximum filename length: %d\n",
      pathconf(".", _PC_NAME_MAX));
  printf("Maximum path length: %d\n",
      pathconf("/", _PC_PATH_MAX));
  printf("Pipe buffer size: %d\n",
      pathconf("/var/spool/cron/FIFO", _PC_PIPE_BUF));
}
