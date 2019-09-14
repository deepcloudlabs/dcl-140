/*
 * list_stats produces a report from the stats heap
 */

#include "sms.h"

void list_stats(void) {     /* Summarise statistics            */
  Stats * sp ;
  int abort_count = 0, client_count = 0, connect = 0, size = 0;

  pthread_mutex_lock(&stat);
  for (sp = history ; sp != NULL ; sp = sp->next) {
    client_count++;
    if (sp->aborted)
      abort_count++;
    connect += sp->connect;
    size += sp->size;
  }
  pthread_mutex_unlock(&stat);

  if (client_count > 0)
    printf("%d connections %4.1f%% aborted, average connect = %.1f"
        " seconds\naverage size = %.1f bytes\n",
        client_count, 100.0*abort_count/client_count,
        (double)connect/client_count,
        (double)size/client_count);
  else
    printf("No connections on record\n");
}
