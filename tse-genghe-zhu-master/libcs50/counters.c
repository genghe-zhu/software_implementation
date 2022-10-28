/* 
 * counters.c - CS50 'counters' module
 *
 * see counters.h for more information.
 *
 * CS50 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "counters.h"
#include "memory.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct countersnode {
  int key;                  // key for this item
  int counter;                 // counter to key
  struct countersnode *next;       // link to next node
} countersnode_t;

/**************** global types ****************/
typedef struct counters {
  struct countersnode *head;       // head of the list of keys in counters
} counters_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see counters.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static countersnode_t *countersnode_new(const int key);

/**************** counters_new() ****************/
/* see counters.h for description */
counters_t *
counters_new(void)
{
  counters_t *counters = count_malloc(sizeof(counters_t));

  if (counters == NULL) {
    return NULL;              // error allocating counters
  } else {
    // initialize contents of counters structure
    counters->head = NULL;
    return counters;
  }
}

/**************** counters_add() ****************/
/* see counters.h for description */
int
counters_add(counters_t *counters, const int key)
{
  if (counters != NULL && key >= 0) {
    int counter = counters_get(counters, key) + 1;
    if (!counters_set(counters, key, counter)) {
      return 0;       // problem during counters_set 
    } else {	
      return counter;
    }
  } 
  return 0;
}

/**************** countersnode_new ****************/
/* Allocate and initialize a countersnode */
static countersnode_t * // not visible outside this file
countersnode_new(const int key)
{
  countersnode_t *node = count_malloc(sizeof(countersnode_t));

  if (node == NULL) {
    // error allocating memory for node; return error
    return NULL;
  } else {
    node->key = key;
    node->counter = 1;
    node->next = NULL;
    return node;
  }
}


/**************** counters_print() ****************/
/* see counters.h for description */
void
counters_print(counters_t *counters, FILE *fp) 
{
  if (fp != NULL) {
    if (counters != NULL) {
      fputc('{', fp);
      for (countersnode_t *node = counters->head; node != NULL; node = node->next) {
        // print this node
	fprintf(fp, "%i=%i,", node->key, node->counter);
      }
      fputc('}', fp);
    } else {
      fputs("(null)", fp);
    }
  }
}

/**************** counters_iterate() ****************/
/* see counters.h for description */
void
counters_iterate(counters_t *counters, void *arg, 
            void (*itemfunc)(void *arg, const int key, const int count) )
{
  if (counters != NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    for (countersnode_t *node = counters->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->key, node->counter);
    }
  }
}

/**************** counters_delete() ****************/
/* see counters.h for description */
void
counters_delete(counters_t *counters)
{
  if (counters != NULL) {
    for (countersnode_t *node = counters->head; node != NULL; ) {
     
      countersnode_t *next = node->next;     // remember what comes next
      count_free(node);                 // free the node
      node = next;                      // and move on to next
    }

    count_free(counters);
  }

#ifdef MEMTEST
  count_report(stdout, "End of counters_delete");
#endif
}
                            

/**************** counters_get() ****************/
/* see counters.h for description */
int
counters_get(counters_t *counters, const int key)
{
  if (counters != NULL) {
    for (countersnode_t *node = counters->head; node != NULL; node = node->next ) {
      if (key == node->key) {
          return node->counter;
      }
    }

  } 
  return 0;                          // for not found key

}

/**************** counters_set() ****************/
/* see counters.h for description */
bool
counters_set(counters_t *counters, const int key, const int count)
{
  if (key < 0 || count < 0) {
    return false;
  }

  if (counters != NULL) {  
    for (countersnode_t *node = counters->head; node != NULL; node = node->next ) {
      if (key == node->key) {
          node->counter = count;
	  return true;
      }
    }

    // allocate a new node to be added to the list
    countersnode_t *new = countersnode_new(key);
    if (new != NULL) {
      // add it to the head of the list
      new->next = counters->head;
      counters->head = new;
      new->counter = count;
      return true;
    } else {
      return false;			 // out of memory
    }
  } 
  return false;                          // for not found key

}
