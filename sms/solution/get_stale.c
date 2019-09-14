/*
 * get_stale merely locates a stale servlet
 * it returns a valid pointer on success
 * it returns NULL if no stale servlets are to be found
 */

#include "sms.h"

Servlet * get_stale(int secs) {       /* find ONE stale client    */
  int now,old;
  Servlet * sp = NULL, * found = NULL;

  now = time(NULL);
  old = now - secs;
  pthread_mutex_lock(&serv);
  for (sp = door->next ; sp != door ; sp = sp->next) {
    if (sp->start < old) {
      found = sp;
      break;
    }
  }
  pthread_mutex_unlock(&serv);
  return found;
}
