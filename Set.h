#ifndef SET_H
#define SET_H

/*
A set of nonnegative integers less than n.

Set creation, insertion, removal, and membership tests are all O(1).
*/

typedef struct Set Set;

Set *Set_create(int n);

void Set_destroy(Set *sptr);

void Set_clear(Set *sptr);

int Set_size(const Set *sptr);

int Set_insert(Set *sptr, int x);

int Set_remove(Set *sptr, int x);

int Set_contains(const Set *sptr, int x);

void Set_print(const Set *sptr);

#endif
