/* 
 * hashtabletest.c - test program for CS50 hashtable module
 *
 * usage: read lines from stdin
 *
 * CS50, Summer 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "memory.h"
#include "readlinep.h"

static void nameprint(FILE *fp, const char *key, void *item);
static void namedelete(void *item);
static void itemcount(void *arg, const char *key, void *item);
static void insertname(hashtable_t *hashtable, const char *key, const char *item);

/* **************************************** */
int main() 
{
  hashtable_t *hashtable;
  int namecount = 0;

  // create a hashtable
  hashtable = hashtable_new(20);
  if (hashtable == NULL) {
    fprintf(stderr, "hashtable_new failed\n");
    return 1;
  }

  printf("Count (should be zero): ");
  hashtable_iterate(hashtable, &namecount, itemcount);
  printf("%d\n", namecount);  

  printf("testing hashtable_insert...\n");
  // read lines from stdin
  namecount = 0;
  insertname(hashtable, "key1", "item1");
  insertname(hashtable, "key2", "item2");
  insertname(hashtable, "key3", "item3");
  insertname(hashtable, "key4", "item4");
  insertname(hashtable, "key5", "item5");

  printf("The hashtable:\n");
  hashtable_print(hashtable, stdout, nameprint);
  printf("\n");

  namecount = 0;
  printf("Count (should be 5): ");
  hashtable_iterate(hashtable, &namecount, itemcount);
  printf("%d\n", namecount);  

  hashtable_insert(hashtable, "key4", "item44");
  hashtable_insert(hashtable, "key3", "item34");
   
  printf("test insert duplicate key, hashtable should not change.\n");
  printf("The hashtable:\n");
  hashtable_print(hashtable, stdout, nameprint);
  printf("\n");

  namecount = 0;
  printf("Count (should be 5): ");
  hashtable_iterate(hashtable, &namecount, itemcount);
  printf("%d\n", namecount);  

  printf("testing hashtable_find..., \n");
  char *name = hashtable_find(hashtable, "key3");
  printf("find key3 for key %s\n", name);

  name = hashtable_find(hashtable, "key6");
  printf("find key6 for key %s\n", name);

  printf("testing hashtable_find..., one key per line\n");
  // read lines from stdin
  namecount = 0;
  while (!feof(stdin)) {
    char *key = readlinep();
    if (key != NULL) {
      char *name = hashtable_find(hashtable, key);
      printf("find %s for key %s\n", name, key);
      
    }
  }


  printf("Count (should be %d): ", namecount);
  namecount = 0;
  hashtable_iterate(hashtable, &namecount, itemcount);
  printf("%d\n", namecount);  

  printf("test with null hashtable, good item...\n");
  hashtable_insert(NULL, "da", "Dartmouth");
  printf("test with null key...\n");
  hashtable_insert(hashtable, NULL, "null"); 
  printf("test with null hashtable, null key...\n");
  hashtable_insert(NULL, NULL, "null");

  printf("The hashtable:\n");
  hashtable_print(hashtable, stdout, nameprint);
  printf("\n");
  printf("Count (should be %d): ", namecount);
  namecount = 0;
  hashtable_iterate(hashtable, &namecount, itemcount);
  printf("%d\n", namecount);  

  printf("delete the hashtable...\n");
  hashtable_delete(hashtable, namedelete);

  return 0;
}


/* count the non-null items in the hashtable.
 * note here we don't care what kind of item is in hashtable.
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
void insertname(hashtable_t *hashtable, const char *key, const char *item)
{
  if (item != NULL) {
    char *name = malloc(1024*sizeof(char)); 
    strcpy(name, item);
    hashtable_insert(hashtable, key, name);
  }

}
// delete a name 
void namedelete(void *item)
{
  if (item != NULL) {
    free(item);   
  }
}
