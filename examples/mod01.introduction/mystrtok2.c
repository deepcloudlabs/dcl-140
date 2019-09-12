#include <string.h>
#include <stdio.h>
main() {

  char *arg;
  char line[] = "ls -a /";

  arg = strtok(line, " \t\n");
  while( arg ) {
    printf("%s\n", arg);
    arg = strtok( (char*)NULL, " \t\n");
  }
}
