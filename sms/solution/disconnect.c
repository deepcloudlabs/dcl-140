/*
 * disconnect is passed a pointer to a Servlet
 * It should perform the following :
 *	1. Take the servlet out of the circular list
 *	3. Close the socket connection
 *	3. Set the closing time
 *	4. Create a Pending item and push the pending stack
 *	5. Alert the garbage collector 
 */

#include "sms.h"

void disconnect(Servlet * done) {
  Pending * zombie;

  pthread_mutex_lock(&serv);
  done->prev->next = done->next;
  done->next->prev = done->prev;
  pthread_mutex_unlock(&serv);
  close(done->fd);
  done->finish = time(NULL);
  zombie = malloc(sizeof(Pending));
  zombie->head = done;
  pthread_mutex_lock(&heap);
  zombie->tail = in_tray;
  in_tray = zombie;
  pthread_mutex_unlock(&heap);
  sem_post(&garbage_time);
}
