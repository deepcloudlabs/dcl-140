/*
 * zero_stats just frees the stats stack
 */

#include "sms.h"

void zero_stats(void) {     /* re-start statistics            */
  Stats * sp, * temp ;

  pthread_mutex_lock(&stat);
  for (sp = history; sp != NULL;) {
    temp = sp;
    sp =  sp->next;
    free(temp);
  }
  history = NULL;
  pthread_mutex_unlock(&stat);
}
