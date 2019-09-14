/*
 * zap_servlet does the following :
 * 	1. append the message to an appropriate file
 *	2. Capture statistics and push onto stats stack
 *	3. Dispose of the Servlet
 */

#include "sms.h"

void zap_servlet(Servlet * victim) {   /* remove and free memory    */
  int out;
  Stats * newstat;
  char mess[50];

  /*  Commit to file */
  if (! victim->aborted) {
    out = open(victim->dest,O_WRONLY | O_CREAT | O_APPEND,0666);
    sprintf(mess,"Message from Customer %x\n",ntohl(victim->cust_ip));
    write(out,mess,strlen(mess));
    write(out,victim->message,victim->chars_read);
    close(out);
  }

  /*  Generate statistics */
  newstat = malloc(sizeof(Stats));
  newstat->cust_ip = victim->cust_ip;
  newstat->size = victim->chars_read;
  strcpy(newstat->dest,victim->dest);
  newstat->connect = 0.5 + (victim->finish - victim->start)/(double)CLK_TCK;
  newstat->aborted = victim->aborted;

  /*  Push onto stats stack */
  pthread_mutex_lock(&stat);     /* lock the stats    */
  newstat->next = history;
  history = newstat;
  pthread_mutex_unlock(&stat);     /* unlock the stats    */
  free(victim);
}
