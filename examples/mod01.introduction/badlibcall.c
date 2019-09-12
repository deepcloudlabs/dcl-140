#include <sys/types.h>
#include <time.h>
#include <stdio.h>
main() {

  time_t t;
  char *then;
  char *now;

  time(&t);

  /* ctime() put the current time into static space */
  then = ctime(&t);

  /* Let time pass for one minute */
  sleep(60);

  time(&t);

  /* ctime() puts new time into same space */
  now = ctime(&t);

  /* then and now point to the same space */
  printf("%s%s", then, now);
}
