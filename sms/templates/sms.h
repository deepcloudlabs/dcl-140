/* sms.h : header file for short message service project 		*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/socket.h>
#include <sys/conf.h>
#include <stropts.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#define DIE(x)   perror(x),exit(errno)
#define SHORTMESS 128
#define MAXDEST 64
#define PORT 5678

/*---------------------------DATA STRUCTURES----------------------------*/
typedef struct str_servlet {
  int fd;				/* Socket connection	*/
  pthread_t thread;			/* For control		*/
  int cust_ip;				/* IP addr of client	*/
  char dest[MAXDEST];			/* addressee		*/
  char message[SHORTMESS];		/* message text		*/
  int chars_read;			/* size of mess so far	*/
  time_t start;				/* Connection opened	*/
  time_t finish;			/* Connection closed	*/
  int aborted;				/* boolean flag		*/
  struct str_servlet * prev;		/* Doubly linked list	*/
  struct str_servlet * next;		/* Doubly linked list	*/
} Servlet;

typedef struct str_stats {
  int cust_ip;				/* IP addr of client	*/
  char dest[MAXDEST];			/* addressee		*/
  int size;				/* message size		*/
  int connect;				/* connect time in secs	*/
  int aborted;				/* boolean flag		*/
  struct str_stats * next;		/* Linked list		*/
} Stats;

typedef struct str_pending {
  Servlet * head;			/* recently terminated	*/
  struct str_pending * tail;		/* linked list		*/
} Pending;

typedef struct {
  char * chat;
  void (* act)(void);
} Menu_item ;



/*---------------------------FUNCTION PROTOTYPES------------------------*/

void * serve_client(void *); 	/* body of servlet thread		*/
void disconnect(Servlet * );	/* close socket,timestamp,alert garbo	*/
void * garbo(void *);		/* garbage collector			*/
Servlet * get_stale(int);	/* find ONE stale client		*/
void list_conn(void);		/* list number of current connections 	*/
void list_stats(void);  	/* Summarise statistics			*/
void * listen_port(void *);	/* body of port listener		*/
void menu(Menu_item *);		/* user interface menu			*/
void zap_stale(void);		/* Call disconnect when needed		*/
void zap_servlet(Servlet *);	/* store info, unlink and free memory	*/
void zero_stats(void);  	/* re-start statistics			*/

/*---------------------------GLOBAL VARIABLES---------------------------*/
extern Servlet * door;		/* entrance to doubly linked list	*/
extern Stats * history;		/* start of stats linked list		*/
extern Pending * in_tray;	/* pile of stale servlets		*/
extern sem_t garbage_time;	/* schedule garbage collection		*/
extern pthread_attr_t attr;	/* set to make ALL threads detached	*/
extern pthread_mutex_t serv;	/* protect servlet dbly linked list	*/
extern pthread_mutex_t stat;	/* protect stats linked list		*/
extern pthread_mutex_t heap;	/* protect heap of undead servlets	*/
