# CS50 Lab 3
## CS50 summer 2020

### hashtable

A hashtable maintains an unordered collection of (key,item) pairs; any given key can only occur in the hashtable once. It starts out empty and grows as the caller inserts new (key,item) pairs. The caller can retrieve items by asking for their key, but cannot remove or update pairs. Items are distinguished by their key.

### Usage

The *hashtable* module, defined in `hashtable.h` and implemented in `hashtable.c` implements a hashtable of `void*` with `char*` keys, and exports the following functions:

```c
hashtable_t *hashtable_new(int num_slots);
bool hashtable_insert(hashtable_t *hashtable, const char *key, void *item);
void *hashtable_find(hashtable_t *hashtable, const char *key);
void hashtable_print(hashtable_t *hashtable, FILE *fp,
               void (*itemprint)(FILE *fp, const char *key, void *item) );
void hashtable_iterate(hashtable_t *hashtable, void *arg,
               void (*itemfunc)(void *arg, const char *key, void *item) );
void hashtable_delete(hashtable_t *hashtable, void (*itemdelete)(void *item) );
```

### Implementation

We implement this hashtable as a set and call the set functions. 
The *hashtable* itself is represented as a `struct hashtable` containing an array; the array is NULL when the hashtable is empty.

### Assumptions

No assumptions beyond those that are clear from the spec.

### Files

* `Makefile` - compilation procedure
* `hashtable.h` - the interface
* `hashtable.c` - the implementation
* `jhash.c` - hash function
* `hashtabletest.c` - unit test driver
* `TESTIMG.md` - testing results

### Compilation

TO compile, simply `make hashtable.o`

### Testing

`hashtabletetst.c` reads lines from stdin and puts them into a hashtable, then pulls the back out
It also tests a few error and edge cases.

To test, `make test`.
