# CS50 Lab 3
## CS50 summer 2020

### counters

A counter set is a set of counters, each distinguished by an integer key. It's a set - each key can only occur once in the set - but instead of storing (key,item) pairs, it tracks a counter for each key. It starts empty. Each time `counters_add` is called on a given key, that key's counter is incremented. The current counter value can be retrieved by asking for the relevant key. 

### Usage

The *counters* module, defined in `counters.h` and implemented in `counters.c` implements a set of integer counters with `int` keys (where keys must be non-negative) and exports the following functions:

```c
counters_t *counters_new(void);
int counters_add(counters_t *counters, const int key);
int counters_get(counters_t *counters, const int key);
bool counters_set(counters_t *counters, const int key);
void counters_print(counters_t *counters, FILE *fp);
void counters_iterate(counters_t *counters, void *arg,
		      void (*itemfunc)(void *arg, const int key, int count));
void counters_delete(counters_t *counters);
```

### Implementation

We implement this counters as a linked list. 
The *counters* itself is represented as a `struct counters` containing a pointer to the head of the list; the head pointer is NULL when the counters is empty.

Each node in the list is a `struct countersnode`, a type defined internally to the module.
Each countersnode includes an `int key` and an `int counter` and a pointer to the next countersnode on the list.

The `counters_new` method initializes a new struct counters by allocating memory and creating a head pointer to NULL.

The `counters_get` method finds the count associated with with the given key by looping through the nodes and comparing the existing keys. 

To insert a new item in the counters we call `counters_add` to see if the key and item already exist, then create a new countersnode to hold the item and insert at the head of the list.

The `counters_set` method sets the current value of counter associated with the given key. If the key does not exist yet, it creates a counter for it and initializes it to the given value.

The `counters_add` method increments the counter indicated by the key by calling `counters_get` and `counters_set`.

The `counters_print` method prints a little syntax around the list, and between the keys and counts, but mostly calls the `itemprint` function on each count and key by scanning the linked list.

The `counters_iterate` method calls `itemfunc` function on each count and key by scanning the linked list.

The `counters_delete` method frees the node by scanning through the linked list. (doesn't need itemfunc because key and counter are both int) 
It concludes by freeing `struct counters`.

### Assumptions

No assumptions beyond those that are clear from the spec.

### Files

* `Makefile` - compilation procedure
* `counters.h` - the interface
* `counters.c` - the implementation
* `counterstest.c` - unit test driver
* `TESTIMG.md` - testing results

### Compilation

TO compile, simply `make counters.o`

### Testing

`counterstetst.c` reads lines from stdin and puts them into a counters, then pulls the back out
It also tests a few error and edge cases.

To test, `make test`.
