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
  return NULL;
}
