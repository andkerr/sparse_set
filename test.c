#include "Set.h"

#include <assert.h>

int main() {
    Set *sp = Set_create(20);
    assert(Set_size(sp) == 0);

    Set_print(sp);

    for (int i = 0; i < 20; ++i) {
        assert( Set_insert(sp, i));
        assert(!Set_insert(sp, i)); // no duplicates
        assert(Set_contains(sp, i));
    }

    Set_print(sp);

    for (int i = 0; i < 20; ++i) {
        assert( Set_remove(sp, i));
        assert(!Set_remove(sp, i));
        Set_print(sp);
    }

    assert(Set_size(sp) == 0);

    Set_destroy(sp);
}
