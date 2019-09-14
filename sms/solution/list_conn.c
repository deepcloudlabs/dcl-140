/*
 * list_conn looks for live connections
 * It reports the total number and the age of the oldest
 */

#include "sms.h"

void list_conn(void) {       /* list number of current connections     */
  int now,stalest,count;
  Servlet * sp;

  stalest = now = time(NULL);
  pthread_mutex_lock(&serv);
  for (count = 0,sp = door->next ; sp != door ; count++, sp = sp->next) {
    if (sp->start < stalest)
      stalest = sp->start;
  }
  pthread_mutex_unlock(&serv);
  printf("There are %d live connections\n",count);
  printf("The oldest began %d seconds ago\n",now - stalest);
}
