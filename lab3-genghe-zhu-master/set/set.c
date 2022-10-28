/* 
 * set.c - CS50 'set' module
 *
 * see set.h for more information.
 *
 * CS50 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
#include "memory.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct setnode {
  char *key;                  // pointer to key for this item
  void *item;                 // pointer to data for this item
  struct setnode *next;       // link to next node
} setnode_t;

/**************** global types ****************/
typedef struct set {
  struct setnode *head;       // head of the list of items in set
} set_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see set.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static setnode_t *setnode_new(const char *key, void *item);

/**************** set_new() ****************/
/* see set.h for description */
set_t *
set_new(void)
{
  set_t *set = count_malloc(sizeof(set_t));

  if (set == NULL) {
    return NULL;              // error allocating set
  } else {
    // initialize contents of set structure
    set->head = NULL;
    return set;
  }
}

/**************** set_insert() ****************/
/* see set.h for description */
bool
set_insert(set_t *set, const char *key, void *item)
{
  if (set != NULL && key != NULL) {
    if (set_find(set, key) == NULL) {
        // allocate a new node to be added to the list
        setnode_t *new = setnode_new(key, item);
        if (new != NULL) {
            // add it to the head of the list
            new->next = set->head;
            set->head = new;
            return true;
	}
    } else {
        return false; // found key
    }
    
  } 
  return false;

#ifdef MEMTEST
  count_report(stdout, "After set_insert");
#endif
}

/**************** setnode_new ****************/
/* Allocate and initialize a setnode */
static setnode_t * // not visible outside this file
setnode_new(const char *key, void *item)
{
  setnode_t *node = count_malloc(sizeof(setnode_t));

  if (node == NULL) {
    // error allocating memory for node; return error
    return NULL;
  } else {
    node->key = count_malloc(1024*sizeof(char));
    strcpy(node->key, key);   
    node->item = item;
    node->next = NULL;
    return node;
  }
}


/**************** set_print() ****************/
/* see set.h for description */
void
set_print(set_t *set, FILE *fp, 
          void (*itemprint)(FILE *fp, const char *key, void *item) )
{
  if (fp != NULL) {
    if (set != NULL) {
      fputc('{', fp);
      for (setnode_t *node = set->head; node != NULL; node = node->next) {
        // print this node
        if (itemprint != NULL) { // print the node's item 
          (*itemprint)(fp, node->key, node->item);
          fputc(',', fp);
        }
      }
      fputc('}', fp);
    } else {
      fputs("(null)", fp);
    }
  }
}

/**************** set_iterate() ****************/
/* see set.h for description */
void
set_iterate(set_t *set, void *arg, 
            void (*itemfunc)(void *arg, const char *key, void *item) )
{
  if (set != NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    for (setnode_t *node = set->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->key, node->item);
    }
  }
}

/**************** set_delete() ****************/
/* see set.h for description */
void
set_delete(set_t *set, void (*itemdelete)(void *item) )
{
  if (set != NULL) {
    for (setnode_t *node = set->head; node != NULL; ) {
     
      if (node->key != NULL) {        
        count_free(node->key);      // delete node's key
      }
      if (itemdelete != NULL) {         // if possible...
        (*itemdelete)(node->item);      // delete node's item
      }
      setnode_t *next = node->next;     // remember what comes next
      count_free(node);                 // free the node
      node = next;                      // and move on to next
    }

    count_free(set);
  }

#ifdef MEMTEST
  count_report(stdout, "End of set_delete");
#endif
}
                            

/**************** set_find() ****************/
/* see set.h for description */
void *
set_find(set_t *set, const char *key)
{
  if (set != NULL) {
    for (setnode_t *node = set->head; node != NULL; node = node->next ) {
      if (strcmp(key, node->key) == 0) {
          return node->item;
      }
    }

  } 
  return NULL;                          // for not found key

}
