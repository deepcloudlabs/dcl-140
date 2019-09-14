/*
 * listen_port is the body of the thread which listens
 * on a particular port number (it's sole argument )
 * Whenever a new connection is requested it calls make_servlet
 * and then fires off a new thread running serve_client
 * It must set two fields in the Servlet structure :
 *	1. fd
 *	2. start
 */

#include "sms.h"

void * listen_port(void * info) {       /* body of port listener    */
  static struct sockaddr_in server;
  int sd,cd;
  int port = * (int *) info;
  Servlet * newhire;
  struct tms timebuff;

  sd = socket(AF_INET,SOCK_STREAM,0);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  if (bind(sd,(struct sockaddr *)&server,sizeof(server)) == -1)
    DIE("failed to make sock");

  listen(sd,5);

  for (;;) {
    cd = accept(sd,NULL,NULL);
    newhire = calloc(sizeof(Servlet),1);
    newhire->fd = cd;
    newhire->start = time(NULL);
    pthread_mutex_lock(&serv);
    newhire->next = door->next;
    newhire->prev = door;
    door->next = newhire;
    pthread_mutex_unlock(&serv);
    pthread_create(& newhire->thread,NULL,serve_client,newhire);
  }
  return NULL;
}
