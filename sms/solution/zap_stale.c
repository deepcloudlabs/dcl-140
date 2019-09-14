/*
 *	zap_stale does the following
 *	foreach stale client found
 *		set abort flag
 *		kill the thread
 *		call disconnect
 */

#include "sms.h"

void zap_stale(void) {        /* Call disconnect when needed		*/
  char line[80];
  Servlet * sp;
  int secs = 0;
  do {
     printf("How many seconds counts as stale ? ");
     secs = atoi(gets(line));
  } while (secs == 0 && printf("%s was a silly thing to type\n",line));

  while ((sp = get_stale(secs)) != NULL) {
    printf("Found a stale one\n");
    sp->aborted = 1;
    write(sp->fd,"Sorry - time is up\n",19);
    pthread_cancel(sp->thread);
    disconnect(sp);
  }
}
