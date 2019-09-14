/*
 * menu : a generalised menu function
 * The argument is the base of an array of Menu_item, which
 * must be suitably NULL-terminated
 */

#include "sms.h"

void menu(Menu_item * menu) {        /* user interface menu        */
  int i, j;
  char line[80];
  for (;;) {
    for (i = 0 ; menu[i].chat != NULL; i++)
      printf("\n\t%d) %s\n",i + 1,menu[i].chat);
    printf("\nPlease choose  (1 - %d) : ",i);
    gets(line);
    j = atoi(line);
    if (j >=1 && j <= i)
      menu[j - 1].act();
    else
      printf("%s was a silly thing to type\n",line);
  }
}
