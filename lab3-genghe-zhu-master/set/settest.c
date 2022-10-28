/* 
 * settest.c - test program for CS50 set module
 *
 * usage: read lines from stdin
 *
 * CS50, Summer 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "memory.h"
#include "readlinep.h"

static void nameprint(FILE *fp, const char *key, void *item);
static void namedelete(void *item);
static void itemcount(void *arg, const char *key, void *item);
static void insertname(set_t *set, const char *key, const char *item);

/* **************************************** */
int main() 
{
  set_t *set;
  int namecount = 0;

  // create a set
  set = set_new();
  if (set == NULL) {
    fprintf(stderr, "set_new failed\n");
    return 1;
  }

  printf("Count (should be zero): ");
  set_iterate(set, &namecount, itemcount);
  printf("%d\n", namecount);  

  printf("testing set_insert...\n");
  // read lines from stdin
  namecount = 0;
  insertname(set, "key1", "item1");
  insertname(set, "key2", "item2");
  insertname(set, "key3", "item3");
  insertname(set, "key4", "item4");
  insertname(set, "key5", "item5");

  printf("The set:\n");
  set_print(set, stdout, nameprint);
  printf("\n");

  namecount = 0;
  printf("Count (should be 5): ");
  set_iterate(set, &namecount, itemcount);
  printf("%d\n", namecount);  

  set_insert(set, "key4", "item44");
  set_insert(set, "key3", "item34");
   
  printf("test insert duplicate key, set should not change.\n");
  printf("The set:\n");
  set_print(set, stdout, nameprint);
  printf("\n");

  namecount = 0;
  printf("Count (should be 5): ");
  set_iterate(set, &namecount, itemcount);
  printf("%d\n", namecount);  

  printf("testing set_find..., \n");
  char *name = set_find(set, "key3");
  printf("find key3 for key %s\n", name);

  name = set_find(set, "key6");
  printf("find key6 for key %s\n", name);

  printf("testing set_find..., one key per line\n");
  // read lines from stdin
  namecount = 0;
  while (!feof(stdin)) {
    char *key = readlinep();
    if (key != NULL) {
      char *name = set_find(set, key);
      printf("find %s for key %s\n", name, key);
      
    }
  }


  printf("Count (should be %d): ", namecount);
  namecount = 0;
  set_iterate(set, &namecount, itemcount);
  printf("%d\n", namecount);  

  printf("test with null set, good item...\n");
  set_insert(NULL, "da", "Dartmouth");
  printf("test with null key...\n");
  set_insert(set, NULL, "null"); 
  printf("test with null set, null key...\n");
  set_insert(NULL, NULL, "null");

  printf("The set:\n");
  set_print(set, stdout, nameprint);
  printf("\n");
  printf("Count (should be %d): ", namecount);
  namecount = 0;
  set_iterate(set, &namecount, itemcount);
  printf("%d\n", namecount);  

  printf("delete the set...\n");
  set_delete(set, namedelete);

  return 0;
}


/* count the non-null items in the set.
 * note here we don't care what kind of item is in set.
 */
static void itemcount(void *arg, const char *key, void *item)
{
  int *nitems = arg;

  if (nitems != NULL && item != NULL)
    (*nitems)++;
}

// print a name, in quotes.
void nameprint(FILE *fp, const char *key, void *item)
{
  if (key == NULL) {
    fprintf(fp, "(null)");
  }
  else {
    fprintf(fp, "\"%s\":", key); 
  }
  char *name = item; 
  if (name == NULL) {
    fprintf(fp, "(null)");
  }
  else {
    fprintf(fp, "\"%s\"", name); 
  }
}


// insert a key item pair
void insertname(set_t *set, const char *key, const char *item)
{
  if (item != NULL) {
    char *name = malloc(1024*sizeof(char)); 
    strcpy(name, item);
    set_insert(set, key, name);
  }

}
// delete a name 
void namedelete(void *item)
{
  if (item != NULL) {
    free(item);   
  }
}
