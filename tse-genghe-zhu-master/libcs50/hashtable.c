/* 
 * hashtable.c - CS50 'hashtable' module
 *
 * see hashtable.h for more information.
 *
 * CS50 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"
#include "jhash.h"
#include "memory.h"
#include "set.h"

/**************** file-local global variables ****************/
/* none */

void nprint(FILE *fp, const char *key, void *item);
/**************** global types ****************/
typedef struct hashtable {
  set_t **set_array;       // head of the list of items in hashtable
  int num_slots;
} hashtable_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see hashtable.h for comments about exported functions */

/**************** hashtable_new() ****************/
/* see hashtable.h for description */
hashtable_t *
hashtable_new(const int num_slots)
{
  hashtable_t *hashtable = count_malloc(sizeof(hashtable_t));

  if (hashtable == NULL) {
    return NULL;              // error allocating hashtable
  } else {
    // initialize contents of hashtable structure
    hashtable->num_slots = num_slots;
    hashtable->set_array = calloc(num_slots, sizeof(set_t*)); 
    for (int i = 0; i < hashtable->num_slots; i++) {
      hashtable->set_array[i] = set_new();
    }
    return hashtable;
  }
}

/**************** hashtable_insert() ****************/
/* see hashtable.h for description */
bool
hashtable_insert(hashtable_t *hashtable, const char *key, void *item)
{
  if (hashtable != NULL && key != NULL) {
    if (hashtable->set_array != NULL) {
      unsigned long i = JenkinsHash(key, hashtable->num_slots);
      return set_insert(hashtable->set_array[i], key, item);

    }
  }
  return false;                          // for not found key

#ifdef MEMTEST
  count_report(stdout, "After hashtable_insert");
#endif
}



/**************** hashtable_print() ****************/
/* see hashtable.h for description */
void
hashtable_print(hashtable_t *hashtable, FILE *fp, 
          void (*itemprint)(FILE *fp, const char *key, void *item) )
{
  if (fp != NULL) {
    if (hashtable != NULL) {
      for (int i = 0; i < hashtable->num_slots; i++) {
        // print this node
        set_print(hashtable->set_array[i], fp, itemprint);
      }
    } else {
      fputs("(null)", fp);
    }
  }
}

/**************** hashtable_iterate() ****************/
/* see hashtable.h for description */
void
hashtable_iterate(hashtable_t *hashtable, void *arg, 
            void (*itemfunc)(void *arg, const char *key, void *item) )
{
  if (hashtable != NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    if (hashtable->set_array != NULL) {
      for (int i = 0; i < hashtable->num_slots; i++) {
	set_iterate(hashtable->set_array[i], arg, itemfunc);	
      }	
    }
  }
}

/**************** hashtable_delete() ****************/
/* see hashtable.h for description */
void
hashtable_delete(hashtable_t *hashtable, void (*itemdelete)(void *item) )
{
  if (hashtable != NULL) {
    if (hashtable->set_array != NULL) {
      for (int i = 0; i < hashtable->num_slots; i++) {
	set_delete(hashtable->set_array[i], itemdelete);
      }
      count_free(hashtable->set_array);
    }
    count_free(hashtable);
  }
#ifdef MEMTEST
  count_report(stdout, "End of hashtable_delete");
#endif
}
                            

/**************** hashtable_find() ****************/
/* see hashtable.h for description */
void *
hashtable_find(hashtable_t *hashtable, const char *key)
{
  if (hashtable != NULL) {
    if (hashtable->set_array != NULL) {
      unsigned long i = JenkinsHash(key, hashtable->num_slots);
      return set_find(hashtable->set_array[i], key);
    }
  } 
  return NULL;                          // for not found key

}
