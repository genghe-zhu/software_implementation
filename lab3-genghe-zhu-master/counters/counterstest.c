/* 
 * counterstest.c - test program for CS50 counters module
 *
 * usage: read lines from stdin
 *
 * CS50, Summer 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "memory.h"
#include "readlinep.h"

static void itemcount(void *arg, const int key, int item);

/* **************************************** */
int main() 
{
  counters_t *counters;
  int keycount = 0;

  // create a counters
  counters = counters_new();
  if (counters == NULL) {
    fprintf(stderr, "counters_new failed\n");
    return 1;
  }

  printf("Count (should be zero): ");
  counters_iterate(counters, &keycount, itemcount);
  printf("%d\n", keycount);  

  printf("testing counters_add...\n");
  // read lines from stdin
  keycount = 0;
  counters_add(counters, 1);
  counters_add(counters, 2);
  counters_add(counters, 3);
  counters_add(counters, 4);
  counters_add(counters, 5);
  counters_add(counters, 1);
  counters_add(counters, 1);

  printf("The counters:\n");
  counters_print(counters, stdout);
  printf("\n");

  keycount = 0;
  printf("Count (should be 5): ");
  counters_iterate(counters, &keycount, itemcount);
  printf("%d\n", keycount);  

  counters_set(counters, 1, 6);
  counters_set(counters, 3, 6);
  counters_set(counters, 20, 4);
   
  printf("Test counter_set, set 1:6, 3:6. 20:4\n");
  printf("The counters:\n");
  counters_print(counters, stdout);
  printf("\n");

  keycount = 0;
  printf("Count (should be 6): ");
  counters_iterate(counters, &keycount, itemcount);
  printf("%d\n", keycount);  

  printf("testing counters_get..., \n");
  int testFind = counters_get(counters, 3);
  printf("find count for key 3: %i\n", testFind);

  testFind = counters_get(counters, 35);
  printf("find count for key that doesn't exist 35: %i\n", testFind);

  printf("test counters_add with null counters...\n");
  printf("%d\n", counters_add(NULL, 1));
  printf("test with negative key...\n");
  printf("%d\n", counters_add(counters, -1)); 
  printf("test with null counters, negativel key...\n");
  printf("%d\n", counters_add(NULL, -1));

  printf("test counters_get with null counters...\n");
  printf("%d\n", counters_get(NULL, 1));
  printf("test with negative key...\n");
  printf("%d\n", counters_get(counters, -1)); 
  printf("test with null counters, negativel key...\n");
  printf("%d\n", counters_get(NULL, -1));

  printf("test counters_set with null counters...\n");
  printf("%d\n", counters_set(NULL, 1 , 1));
  printf("test with negative key...\n");
  printf("%d\n", counters_set(counters, -1, 1)); 
  printf("test with negative count...\n");
  printf("%d\n", counters_set(counters, 1, -1));

  printf("The counters:\n");
  counters_print(counters, stdout);
  printf("\n");
  printf("Count (should be %d): ", keycount);
  keycount = 0;
  counters_iterate(counters, &keycount, itemcount);
  printf("%d\n", keycount);  

  printf("delete the counters...\n");
  counters_delete(counters);

  return 0;
}


/* count the non-null items in the counters.
 * note here we don't care what kind of item is in counters.
 */
static void itemcount(void *arg, const int key, const int count)
{
  int *nitems = arg;

  if (nitems != NULL && key >= 0)
    (*nitems)++;
}

