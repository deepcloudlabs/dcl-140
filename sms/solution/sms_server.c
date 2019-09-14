/*
 * sms.c : contains 
 *	1. All global variables as defined in sms.h
 *	2. The menu structure
 *	main, which does the following
 *		a) Initialize the circular list
 *		b) Fire off threads for garbo and listen_port
 *		c) Run the menu
 */

#include "sms.h"

Servlet * door;		/* entrance to doubly linked list	*/
Stats * history;	/* start of stats linked list		*/
Pending * in_tray;	/* pile of stale servlets		*/
sem_t garbage_time;	/* schedule garbage collection		*/
pthread_attr_t attr;	/* set to make ALL threads detached	*/
pthread_mutex_t serv;	/* protect servlet dbly linked list	*/
pthread_mutex_t stat;	/* protect stats linked list		*/
pthread_mutex_t heap;	/* protect heap of undead servlets	*/

Menu_item choice[] = {
  { "List number of current connections",list_conn },
  { "Summarise statistics",list_stats },
  { "Re-start statistics",zero_stats },
  { "Zap stale clients and free memory",zap_stale},
  { NULL, NULL }
} ;

main(int argc, char **argv) {
  int port = PORT;
  if (argc == 2)
    port = atoi(argv[1]);

  door = calloc(sizeof(Servlet),1);
  door->prev = door->next = door;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
  pthread_create(NULL,&attr,listen_port,&port);
  pthread_create(NULL,&attr,garbo,NULL);
  menu(choice);
}
