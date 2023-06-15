#include "Set.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * TODO
 *
 * Set_print can always produce sorted output, just iterate over [0, n) and
 * print values for which Set_contains returns true
 *
 * Set_contains may benefit from an private implementation that assumes
 * the value being queried is already in [0, n). The implementation could call
 * it directly and not pay the cost of Set_val_out_of_range, and the public
 * version could validate its input first.
*/

/* This representation uses twice the memory footprint of an ordinary bitmap
representation in return for constant time initialization and 'clear'
operations. Its use is most appropriate when memory is readily available, the
sets being represented are sparse, and clearing / reinitializing sets is common.
*/
struct Set {
    int *dense, *sparse, size, max;
};

int Set_contains_private(const Set *sptr, int x);
int Set_val_out_of_range(const Set *sptr, int x);

void *emalloc(size_t n);

Set *Set_create(int n)
{
    if (n < 1) {
        return NULL; // such a set would be empty
    }

    Set *sptr   = emalloc(sizeof(Set));
    sptr->dense  = emalloc(n * sizeof(int));
    sptr->sparse = emalloc(n * sizeof(int));
    sptr->size   = 0;
    sptr->max    = n - 1;
    return sptr;
}

void Set_destroy(Set *sptr)
{
    free(sptr->dense);
    free(sptr->sparse);
    free(sptr);
}

void Set_clear(Set *sptr)
{
    sptr->size = 0;
}

int Set_size(const Set *sptr)
{
    return sptr->size;
}

int Set_insert(Set *sptr, int x)
{
    if (x > sptr->max || Set_contains(sptr, x)) {
        return 0;
    }

    sptr->dense[sptr->size] = x;
    sptr->sparse[x] = sptr->size;
    ++sptr->size;
    return 1;
}

int Set_remove(Set *sptr, int x)
{
    if (Set_val_out_of_range(sptr, x) || !Set_contains(sptr, x)) {
        return 0;
    }

    int idx = sptr->sparse[x];
    assert(0 <= idx && idx < sptr->size); // x should be somewhere in dense
    sptr->dense[idx] = sptr->dense[--sptr->size];
    sptr->sparse[sptr->dense[idx]] = idx;
    return 1;
}

int Set_contains(const Set *sptr, int x)
{
    if (Set_val_out_of_range(sptr, x)) {
        return 0;
    }

    int idx = sptr->sparse[x];
    return 0 <= idx && idx < sptr->size && sptr->dense[idx] == x;
}

int Set_val_out_of_range(const Set *sptr, int x)
{
    return x < 0 || sptr->max < x;
}

void Set_print(const Set *sptr)
{
    printf("%s", "{ ");
    for (int i = 0; i < sptr->size; ++i) {
        printf("%d ", sptr->dense[i]);
    }
    printf("%s", "}\n");
}

void *emalloc(size_t n)
{
    void *p = malloc(n);
    if (!p) {
        fprintf(stderr, "malloc error, need %zu bytes", n);
        exit(1);
    }
    return p;
}
