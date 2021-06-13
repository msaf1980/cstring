#include <cstring/number.h>

#include <limits.h>
#include <string.h>

#include "benchutils.h"

void bench_cstring_ll2str_min() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        char s[CSTRING_LLSTR_SIZE];
        cstring_ll2str(s, 1LL);
    }
    duration = BENCH_DURATION(start);
    
    bench_print("cstring_ll2str min", duration, n * 2);
}

void bench_cstring_ll2str_max() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        char s[CSTRING_LLSTR_SIZE];
        cstring_ll2str(s, LLONG_MAX);
    }
    duration = BENCH_DURATION(start);
    
    bench_print("cstring_ll2str max", duration, n * 2);
}

void bench_sprintf_ll_min() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        char s[CSTRING_LLSTR_SIZE];
        sprintf(s, "%lld", 1LL);
        sprintf(s, "%lld", LLONG_MAX);
    }
    duration = BENCH_DURATION(start);
    
    bench_print("sprintf(long_long) min", duration, n * 2);
}

void bench_sprintf_ll_max() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        char s[CSTRING_LLSTR_SIZE];
        sprintf(s, "%lld", LLONG_MAX);
    }
    duration = BENCH_DURATION(start);
    
    bench_print("sprintf(long_long) max", duration, n * 2);
}

void bench_sprintf_int_min() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        char s[CSTRING_LLSTR_SIZE];
        sprintf(s, "%d", 1);
    }
    duration = BENCH_DURATION(start);
    
    bench_print("sprintf(int) min", duration, n * 2);
}


void bench_sprintf_int_max() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        char s[CSTRING_LLSTR_SIZE];
        sprintf(s, "%d", INT_MAX);
    }
    duration = BENCH_DURATION(start);
    
    bench_print("sprintf(int) max", duration, n * 2);
}

void bench_sprintf_char_min() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        char s[CSTRING_LLSTR_SIZE];
        sprintf(s, "%c", 1);
    }
    duration = BENCH_DURATION(start);
    
    bench_print("sprintf(char) min", duration, n * 2);
}

void bench_sprintf_char_max() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        char s[CSTRING_LLSTR_SIZE];
        sprintf(s, "%c", CHAR_MAX);
    }
    duration = BENCH_DURATION(start);
    
    bench_print("sprintf(char) max", duration, n * 2);
}

void bench_cstring_ull2str_min() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        char s[CSTRING_LLSTR_SIZE];
        cstring_ull2str(s, 1ULL);
    }
    duration = BENCH_DURATION(start);
    
    bench_print("cstring_ull2str min", duration, n * 2);
}

void bench_cstring_ull2str_max() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        char s[CSTRING_LLSTR_SIZE];
        cstring_ull2str(s, ULLONG_MAX);
    }
    duration = BENCH_DURATION(start);
    
    bench_print("cstring_ull2str max", duration, n * 2);
}

void bench_sprintf_ull_min() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        char s[CSTRING_LLSTR_SIZE];
        sprintf(s, "%llu", 1ULL);
    }
    duration = BENCH_DURATION(start);
    
    bench_print("sprintf(u_long_long) min", duration, n * 2);
}

void bench_sprintf_ull_max() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        char s[CSTRING_LLSTR_SIZE];
        sprintf(s, "%lld", LLONG_MAX);
    }
    duration = BENCH_DURATION(start);
    
    bench_print("sprintf(u_long_long) max", duration, n * 2);
}

void bench_burn() {
    size_t n = 1000000;
    size_t i;
    bench_ns_t start, duration;

    char s[1024];

    for (i = 0; i < n; i++) {
        size_t n = i * 2;
        (void) n;
    }
}

int main(int argc, const char *argv[]) {
    bench_burn();

    bench_sprintf_char_max();
    bench_sprintf_int_max();
    bench_sprintf_ll_max();
    bench_cstring_ll2str_max();

    printf("\n");

    bench_sprintf_ull_max();
    bench_cstring_ull2str_max();

    printf("\n");

    bench_sprintf_char_min();
    bench_sprintf_int_min();
    bench_sprintf_ll_min();
    bench_cstring_ll2str_min();

    printf("\n");

    bench_sprintf_ull_min();
    bench_cstring_ull2str_min();

    return 0;
}
