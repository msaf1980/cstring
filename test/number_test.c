#include <cstring/number.h>

#include <limits.h>
#include <string.h>

#define CTEST_MAIN
#define CTEST_SEGFAULT

#include "ctest.h"

CTEST(number, cstring_ll2str) {
    char sp[CSTRING_LLSTR_SIZE];
    char s[CSTRING_LLSTR_SIZE];
    size_t n;

    n = cstring_ll2str(s, 0LL);
    ASSERT_EQUAL_D(1, n, "0 string length mismatch");
    ASSERT_STR("0", s);

    n = cstring_ll2str(s, 1LL);
    ASSERT_EQUAL_D(1, n, "1 string length mismatch");
    ASSERT_STR("1", s);

    n = cstring_ll2str(s, 9456LL);
    ASSERT_EQUAL_D(4, n, "9456 string length mismatch");
    ASSERT_STR("9456", s);

    n = cstring_ll2str(s, LLONG_MAX);
    sprintf(sp, "%lld", LLONG_MAX);
    ASSERT_STR(sp, s);

    /* Negative number */
    n = cstring_ll2str(s, -1LL);
    ASSERT_EQUAL_D(2, n, "-1 string length mismatch");
    ASSERT_STR("-1", s);

    n = cstring_ll2str(s, -2456LL);
    ASSERT_EQUAL_D(5, n, "-2456 string length mismatch");
    ASSERT_STR("-2456", s);

    n = cstring_ll2str(s, LLONG_MIN);
    sprintf(sp, "%lld", LLONG_MIN);
    ASSERT_STR(sp, s);
}

CTEST(number, cstring_ull2str) {
    char sp[256];
    char s[CSTRING_LLSTR_SIZE];
    size_t n;

    n = cstring_ull2str(s, 0ULL);
    ASSERT_EQUAL_D(1, n, "0 string length mismatch");
    ASSERT_STR("0", s);

    n = cstring_ull2str(s, 1ULL);
    ASSERT_EQUAL_D(1, n, "1 string length mismatch");
    ASSERT_STR("1", s);

    n = cstring_ull2str(s, 9456ULL);
    ASSERT_EQUAL_D(4, n, "9456 string length mismatch");
    ASSERT_STR("9456", s);

    n = cstring_ull2str(s, ULLONG_MAX);
    sprintf(sp, "%llu", ULLONG_MAX);
    ASSERT_STR(sp, s);
}

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}
