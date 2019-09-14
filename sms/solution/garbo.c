/*
 * garbo has the following responsibilities :
 * 	1. call zap_servlet
 *	2. remove the head of the pending tray
 *	garbo is activated by the garbage_time semaphore
 */

#include "sms.h"

void * garbo(void * info) {       /* garbage collector        */
  Pending * temp;

  for (;;) {
    sem_wait(&garbage_time);
    pthread_mutex_lock(&heap);     /* no new zombies    */
    while (in_tray != NULL) {
      zap_servlet(in_tray->head);
      temp = in_tray;
      in_tray = in_tray->tail;
      free(temp);
    }
    pthread_mutex_unlock(&heap);    /* zombies welcome    */
  }
  return NULL;
}
