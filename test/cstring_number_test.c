#include <cstring/cstring.h>
#include <cstring/number.h>

#include <limits.h>
#include <stdio.h>
#include <string.h>

#include "ctest.h"


CTEST(cstring_number, cstring_ll) {
    char sp[2 * CSTRING_LLSTR_SIZE + 1];
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 0, NULL));

    cstring_ll(&s, LLONG_MAX);
    sprintf(sp, "%lld", LLONG_MAX);
    ASSERT_STR_D(sp, s.data, "long long conversion is invalid");

    cstring_ll(&s, LLONG_MIN);
    sprintf(sp, "%lld", LLONG_MIN);
    ASSERT_STR_D(sp, s.data, "long long conversion is invalid");

    cstring_free(&s);
}

CTEST(cstring_number, cstring_ll_cat) {
    char sp[2 * CSTRING_LLSTR_SIZE + 1];
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 0, NULL));

    cstring_ll_cat(&s, LLONG_MAX);
    sprintf(sp, "%lld", LLONG_MAX);
    ASSERT_STR_D(sp, s.data, "long long append is invalid");

    cstring_cat(&s, " ");
    cstring_ll_cat(&s, LLONG_MIN);
    sprintf(sp, "%lld %lld", LLONG_MAX, LLONG_MIN);
    ASSERT_STR_D(sp, s.data, "long long append is invalid");

    cstring_free(&s);
}
