#include <sys/stat.h>

main() {
  struct stat buf;

  if (stat("file", &buf)) {
    perror ("Couldn't stat file");
  } else {

    /* S_ISDIR defined in <sys/stat.h> */
    if (S_ISDIR(buf.st_mode)) {
      printf("It is a directory!\n");
    }
  }
}
