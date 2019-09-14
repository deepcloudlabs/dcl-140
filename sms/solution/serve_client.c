/*
 * serve-client is the body of the thread of which one is started
 * for each client. It receives as its argument a pointer to Servlet
 * of which precisely two fields : the start time and the socket
 * descriptor are non-null.
 * The main duty of this thread is to conduct a dialog with the client.
 * Correct termination is the string "---" in a line by itself.
 * Incorrect termination and over verbose clients must be suitably
 * handled.
 */
#include "sms.h"

void * serve_client(void * info) {   /* body of servlet thread    */
  FILE * in;
  Servlet * me = (Servlet *) info;
  char * p;
  char line[255];
  int len;
  struct sockaddr_in peer;
  int peerlen = sizeof(struct sockaddr_in);

  getpeername(me->fd,(struct sockaddr *)&peer,&peerlen);
  me->cust_ip = peer.sin_addr.s_addr;
  ioctl(me->fd,I_SETCLTIME,0);	/* no delay on closing socket */
  in = fdopen(me->fd,"r");
  write(me->fd,"Destination : ",14);
  fgets(me->dest,MAXDEST,in);
  me->dest[strlen(me->dest) - 2] = '\0';
  write(me->fd,"Now write your message: finish with ---\n",40);
  if (( p = strchr(me->dest,'\n')) != NULL)
    *p = '\0';
  for (;;) {
    write(me->fd,"--> ",4);
    fgets(line,255,in);
    len = strlen(line);
    if (len + me->chars_read > SHORTMESS) {
      write(me->fd,"Message too long !!\n",20);
      me->aborted = 1;
      break;
    }
    if (strncmp(line,"---",3) == 0)
      break;
    strcat(me->message,line);
    me->chars_read += len;
  }
  write(me->fd,"Bye Bye!\n\n",10);
  disconnect(me);
  return NULL;
}
