#include <stdio.h>

int main( int argc, char **argv) {

  char **tmp;

  for( tmp = argv; *tmp != NULL; tmp++ ) {
    printf("Argument %d = %s\n", tmp - argv, *tmp);
  }
  return 0;
}
