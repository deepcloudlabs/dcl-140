/*
 * fifo_server : listen on a named pipe; do lookup ; reply
 *               down another named pipe, the name of which
 *               will be sent by the client (in cli.id)
 *               argv[1] is the name of the local fil
 *               argv[2] is the name of the "well-known" FIFO
 */

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#include "dict.h"

int main(int argc, char **argv) {
  struct stat stbuff;
  int read_fd,write_fd;
  Client cli;
  Dictrec tryit;

  if (argc != 3) {
    fprintf(stderr,"Usage : %s <dictionary source> "
        "<resource / FIFO>\n",argv[0]);
    exit(errno);
  }

  /* Check for existence of dictionary and FIFO (both must exist) */
  if (stat(argv[1],&stbuff) == -1)
    DIE(argv[1]);
  if (stat(argv[2],&stbuff) == -1)
    DIE(argv[2]);
  if (!S_ISFIFO(stbuff.st_mode)) {
    fprintf(stderr,"%s is not a pipe\n",argv[2]);
    exit(errno);
  }

  /* Open FIFO for reading (blocks until a client connects) */
  if ((read_fd = open(argv[2],O_RDONLY)) == -1)
    DIE(argv[2]);

  /* Sit in a loop. lookup word sent and send reply down the given FIFO */
  for (;;) {

    /* Read request and attempt to open reply FIFO */
    if (read(read_fd,&cli,sizeof(Client))== 0) {
      close (read_fd);
      if ((read_fd = open(argv[2],O_RDONLY)) == -1)
        DIE(argv[2]);
      continue;
    }

    strcpy(tryit.word,cli.word);
    write_fd = open(cli.id,O_WRONLY);

    /* lookup the word , handling the different cases appropriately */
    switch(lookup(&tryit,argv[1]) ) {
      case FOUND: 
        write(write_fd,tryit.text,strlen(tryit.text) + 1);
        break;
      case NOTFOUND: 
        write(write_fd,"XXXX",5);
        break;
      case UNAVAIL:
	DIE(argv[1]);
    }

    /* close connection to this client (server is stateless) */
    close(write_fd);
  }
}
