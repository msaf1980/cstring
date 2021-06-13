#include <cstring/cstring.h>

#include <string.h>

#define CTEST_MAIN
#define CTEST_SEGFAULT

#include "ctest.h"

CTEST(cstring, cstring_init_default) {
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 1024, NULL));
    ASSERT_EQUAL_U_D(1024, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[0], "'\0' not set at the end");

    cstring_free(&s);
    ASSERT_EQUAL_U_D(0, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_NULL_D(s.data, "data not set to NULL");
}

CTEST(cstring, cstring_init_zero_default) {
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 0, NULL));

    ASSERT_EQUAL_U_D(0, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_NULL_D(s.data, "data not set to NULL");
}

CTEST(cstring, cstring_attach) {
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    size_t blen = 1024;
    char *buf = malloc(blen);
    strcpy(buf, "test");
    size_t len = strlen(buf);

    cstring_attach(&s, buf, len, blen, NULL);
    ASSERT_EQUAL_U_D(blen-1, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(len, s.size, "size is incorrect");
    ASSERT_STR_D("test", s.data, "string was not correct truncated");
    ASSERT_EQUAL_D((intptr_t) buf, (intptr_t) s.data, "buffer not attached");

    cstring_free(&s);
    ASSERT_EQUAL_U_D(0, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_NULL_D(s.data, "data not set to NULL");
}

CTEST(cstring, cstring_attach_static) {
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    char buf[8];
    strcpy(buf, "test");
    size_t len = strlen(buf);

    cstring_attach(&s, buf, len, sizeof(buf), &c_allocator_none);
    ASSERT_EQUAL_U_D(7, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(len, s.size, "size is incorrect");
    ASSERT_STR_D("test", s.data, "string was not correct truncated");
    ASSERT_EQUAL_D((intptr_t) buf, (intptr_t) s.data, "buffer not attached");

    cstring_free(&s);
    ASSERT_EQUAL_U_D(0, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_NULL_D(s.data, "data not set to NULL");

    ASSERT_EQUAL(-1, cstring_reserve(&s, 512));
    ASSERT_NULL(cstring_cpy(&s, "test"));

    ASSERT_EQUAL(-1, cstring_init(&s, 1024, &c_allocator_none));

}

CTEST(cstring, cstring_reserve) {
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 1024, NULL));
    ASSERT_EQUAL_U_D(1024, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");

    ASSERT_EQUAL(0, cstring_reserve(&s, 4096));
    ASSERT_EQUAL_U_D(4096, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");

    ASSERT_EQUAL(0, cstring_reserve(&s, 512));
    ASSERT_EQUAL_U_D(512, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");

    /* fill string for truncate test */
    s.size = 16;
    strcpy(s.data, "0123456789ABCDEF");
    ASSERT_EQUAL(0, cstring_reserve(&s, 10));
    ASSERT_EQUAL_U_D(10, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(10, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("0123456789", s.data, "string was not correct truncated");

    ASSERT_EQUAL(0, cstring_reserve(&s, 0));
    ASSERT_EQUAL_U_D(0, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_NULL_D(s.data, "data not set to NULL");

    /* not needed, free at reserve 0, but added for test */
    cstring_free(&s);
}

CTEST(cstring, cstring_trunc) {
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 1024, NULL));
    ASSERT_EQUAL_U_D(1024, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");

    /* fill string for truncate test */
    s.size = 16;
    strcpy(s.data, "0123456789ABCDEF");
    cstring_trunc(&s, 10);
    ASSERT_EQUAL_U_D(1024, s.capacity, "capacity is incorrect");
    ASSERT_EQUAL_U_D(10, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("0123456789", s.data, "string was not correct truncated");

    cstring_free(&s);
}

CTEST(cstring, cstring_cpy) {
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 0, NULL));

    ASSERT_NULL(cstring_cpy(&s, NULL));
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_NULL_D(s.data, "data not set to NULL");

    ASSERT_NOT_NULL(cstring_cpy(&s, ""));
    ASSERT_TRUE_D(s.capacity > 0, "capacity is incorrect");
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("", s.data, "string was not correct copied");

    ASSERT_NOT_NULL(cstring_cpy(&s, "0123456789ABCDEF"));
    ASSERT_TRUE_D(s.capacity > 16, "capacity is incorrect");
    ASSERT_EQUAL_U_D(16, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("0123456789ABCDEF", s.data, "string was not correct copied");

    ASSERT_NOT_NULL(cstring_cpy(&s, "X 0123456789ABCDEF 0123456789ABCDEF 0123456789ABCDEF"));
    ASSERT_TRUE_D(s.capacity > 16, "capacity is incorrect");
    ASSERT_EQUAL_U_D(52, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("X 0123456789ABCDEF 0123456789ABCDEF 0123456789ABCDEF", s.data, "string was not correct copied");

    cstring_free(&s);
}

CTEST(cstring, cstring_ncpy) {
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 0, NULL));

    ASSERT_NULL(cstring_ncpy(&s, NULL, 1));
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_NULL_D(s.data, "data not set to NULL");

    ASSERT_NOT_NULL(cstring_ncpy(&s, "", 0));
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_STR_D("", s.data, "string was not correct copied");

    cstring_ncpy(&s, "TEST", 1);
    ASSERT_EQUAL_U_D(1, s.size, "size is incorrect");
    ASSERT_TRUE_D(s.capacity > s.size, "capacity is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("T", s.data, "string was not correct copied");

    cstring_ncpy(&s, "0123456789ABCDEF", 3);
    ASSERT_EQUAL_U_D(3, s.size, "size is incorrect");
    ASSERT_TRUE_D(s.capacity > s.size, "capacity is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("012", s.data, "string was not correct copied");

    cstring_ncpy(&s, "TEST", 8);
    ASSERT_EQUAL_U_D(4, s.size, "size is incorrect");
    ASSERT_TRUE_D(s.capacity > s.size, "capacity is incorrect");    
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("TEST", s.data, "string was not correct copied");

    cstring_free(&s);
}

CTEST(cstring, cstring_lncpy) {
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 0, NULL));

    ASSERT_NULL(cstring_lncpy(&s, NULL, 1));
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_NULL_D(s.data, "data not set to NULL");

    ASSERT_NOT_NULL(cstring_lncpy(&s, "", 0));
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_STR_D("", s.data, "string was not correct copied");

    cstring_lncpy(&s, "TEST", 1);
    ASSERT_EQUAL_U_D(1, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("T", s.data, "string was not correct copied");

    cstring_lncpy(&s, "0123456789ABCDEF", 3);
    ASSERT_EQUAL_U_D(3, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("012", s.data, "string was not correct copied");

    cstring_lncpy(&s, "TEST", 8);
    ASSERT_EQUAL_U_D(4, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("TEST", s.data, "string was not correct copied");

    ASSERT_EQUAL(0, cstring_reserve(&s, 5));
    cstring_lncpy(&s, "TEST", 8);
    ASSERT_EQUAL_U_D(4, s.size, "size is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("TEST", s.data, "string was not correct copied");

    cstring_free(&s);
}

CTEST(cstring, cstring_cat) {
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 0, NULL));

    ASSERT_NULL(cstring_cat(&s, NULL));
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_NULL_D(s.data, "data not set to NULL");

    ASSERT_NOT_NULL(cstring_cat(&s, ""));
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_STR_D("", s.data, "string was not correct copied");

    cstring_cat(&s, "0123456789ABCDEF");
    ASSERT_EQUAL_U_D(16, s.size, "size is incorrect");
    ASSERT_TRUE_D(s.capacity > s.size, "capacity is incorrect");    
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("0123456789ABCDEF", s.data, "string was not correct copied");

    cstring_cat(&s, " 0123456789ABCDEF 0123456789ABCDEF");
    ASSERT_EQUAL_U_D(50, s.size, "size is incorrect");
    ASSERT_TRUE_D(s.capacity > s.size, "capacity is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("0123456789ABCDEF 0123456789ABCDEF 0123456789ABCDEF", s.data, "string was not correct concatenated");

    cstring_free(&s);
}

CTEST(cstring, cstring_ncat) {
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 0, NULL));

    ASSERT_NULL(cstring_ncat(&s, NULL, 1));
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_NULL_D(s.data, "data not set to NULL");

    ASSERT_NOT_NULL(cstring_ncat(&s, "", 0));
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_STR_D("", s.data, "string was not correct copied");

    cstring_ncat(&s, "0123456789ABCDEF", 4);
    ASSERT_EQUAL_U_D(4, s.size, "size is incorrect");
    ASSERT_TRUE_D(s.capacity > s.size, "capacity is incorrect");    
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("0123", s.data, "string was not correct copied");

    cstring_ncat(&s, " 0123456789ABCDEF 0123456789ABCDEF", 4);
    ASSERT_EQUAL_U_D(8, s.size, "size is incorrect");
    ASSERT_TRUE_D(s.capacity > s.size, "capacity is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("0123 012", s.data, "string was not correct concatenated");

    cstring_free(&s);
}

CTEST(cstring, cstring_lncat) {
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 0, NULL));

    ASSERT_NULL(cstring_lncat(&s, NULL, 1));
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_NULL_D(s.data, "data not set to NULL");

    ASSERT_NOT_NULL(cstring_lncat(&s, "", 0));
    ASSERT_EQUAL_U_D(0, s.size, "size is incorrect");
    ASSERT_STR_D("", s.data, "string was not correct copied");

    ASSERT_NOT_NULL(cstring_lncat(&s, "0123456789ABCDEF", 20));
    ASSERT_EQUAL_U_D(16, s.size, "size is incorrect");
    ASSERT_TRUE_D(s.capacity > s.size, "capacity is incorrect");    
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("0123456789ABCDEF", s.data, "string was not correct copied");

    ASSERT_NOT_NULL(cstring_lncat(&s, " TEST", 2));
    ASSERT_EQUAL_U_D(18, s.size, "size is incorrect");
    ASSERT_TRUE_D(s.capacity > s.size, "capacity is incorrect");
    ASSERT_EQUAL_D('\0', s.data[s.size], "'\0' not set at the end of data");
    ASSERT_STR_D("0123456789ABCDEF T", s.data, "string was not correct concatenated");

    cstring_free(&s);
}

CTEST(cstring, cstring_printf_cat) {
    char buf[2048];
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 0, NULL));

    ASSERT_EQUAL_D(9, cstring_printf_cat(&s, "%d %s 12", 1, "TEST"), "string was not correct copied");
    ASSERT_STR_D("1 TEST 12", s.data, "string was not correct copied");

    ASSERT_EQUAL_D(22, cstring_printf_cat(&s, " 56 %.2f %.2f", 1.451, 1.457), "string was not correct copied");
    ASSERT_STR_D("1 TEST 12 56 1.45 1.46", s.data, "string was not correct copied");

    sprintf(buf, "%s%1026d", s.data, 1);
    ASSERT_EQUAL_D(1048, cstring_printf_cat(&s, "%1026d", 1), "string was not correct copied");
    ASSERT_STR_D(buf, s.data, "string was not correct copied");

    cstring_free(&s);
}

CTEST(cstring, cstring_printf_ucat) {
    cstring_t s;
    c_allocator_default_init(); /* init default allocator */

    ASSERT_EQUAL(0, cstring_init(&s, 20, NULL));

    ASSERT_EQUAL_D(9, cstring_nprintf_cat(&s, "%d %s 12", 1, "TEST"), "string was not correct copied");
    ASSERT_STR_D("1 TEST 12", s.data, "string was not correct copied");

    // not full string concatenated for prevent overflow
    ASSERT_EQUAL_D(22, cstring_nprintf_cat(&s, " 56 %.2f %.2f", 1.451, 1.457), "string was not correct copied");
    ASSERT_STR_D("1 TEST 12 56 1.45 1.", s.data, "string was not correct copied");
    ASSERT_EQUAL_D(20, s.size, "string size was not correct");

    cstring_free(&s);
}

int main(int argc, const char *argv[]) {
    return ctest_main(argc, argv);
}
