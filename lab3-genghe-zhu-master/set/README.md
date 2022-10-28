# CS50 Lab 3
## CS50 summer 2020

### set

A set maintains an unordered collection of (key,item) pairs; any given key can only occur in the set once. It starts out empty and grows as the caller inserts new (key,item) pairs. The caller can retrieve items by asking for their key, but cannot remove or update pairs. Items are distinguished by their key.

### Usage

The *set* module, defined in `set.h` and implemented in `set.c` implements a set of `void*` with `char*` keys, and exports the following functions:

```c
set_t *set_new(void);
bool set_insert(set_t *set, const char *key, void *item);
void *set_find(set_t *set, const char *key);
void set_print(set_t *set, FILE *fp,
               void (*itemprint)(FILE *fp, const char *key, void *item) );
void set_iterate(set_t *set, void *arg,
               void (*itemfunc)(void *arg, const char *key, void *item) );
void set_delete(set_t *set, void (*itemdelete)(void *item) );
```

### Implementation

We implement this set as a linked list. 
The *set* itself is represented as a `struct set` containing a pointer to the head of the list; the head pointer is NULL when the set is empty.

Each node in the list is a `struct setnode`, a type defined internally to the module.
Each setnode includes a pointer to the `void *item` and a pointer to the `char *key` and a pointer to the next setnode on the list.

The `set_find` method finds the item associated with with the given key by looping through the set and comparing the existing keys. 

To insert a new item in the set we call `set_find` to see if the key and item already exist, then create a new setnode to hold the item and insert at the head of the list.

The `set_print` method prints a little syntax around the list, and between the keys and items, but mostly calls the `itemprint` function on each item and key by scanning the linked list.

The `set_iterate` method calls `itemfunc` function on each item and key by scanning the linked list.

The `set_delete` method calls `itemdelete` function on each item and frees the key and node by scanning through the linked list. 
It concludes by freeing `struct set`.

### Assumptions

No assumptions beyond those that are clear from the spec.

### Files

* `Makefile` - compilation procedure
* `set.h` - the interface
* `set.c` - the implementation
* `settest.c` - unit test driver
* `TESTIMG.md` - testing results

### Compilation

TO compile, simply `make set.o`

### Testing

`settetst.c` reads lines from stdin and puts them into a set, then pulls the back out
It also tests a few error and edge cases.

To test, `make test`.
