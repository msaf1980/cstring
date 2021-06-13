#include <cstring/cstring.h>
#include <cstring/number.h>

#include <limits.h>
#include <string.h>

#include "benchutils.h"

const char *t = "qwertyuioZXCVBNMpasASDFGHJKLdfghjklzxcvbnmQWERTYUIOP0123456789qwertyuioZXCVBNMpasASDFGHJKLdfghjklzxcvbnmQWERTYUIOP0123456789";

void bench_cstring_cpy_norealloc() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, 1024, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_cpy(&s, t);
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);
    
    bench_print("cstring_cpy_norealloc", duration, n);
}

void bench_cstring_ucpy_norealloc() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, 1024, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_ucpy(&s, t);
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);
    
    bench_print("cstring_ucpy_norealloc", duration, n);
}

void bench_cstring_uncpy_norealloc() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, 1024, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_uncpy(&s, t, strlen(t));
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);
    
    bench_print("cstring_uncpy_norealloc", duration, n);
}

void bench_cstring_lncpy_norealloc() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, 1024, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_lncpy(&s, t, s.capacity);
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);
    
    bench_print("cstring_lncpy_norealloc", duration, n);
}

void bench_cstring_ulncpy_norealloc() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, 1024, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_ulncpy(&s, t, s.capacity);
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);
    
    bench_print("cstring_ulncpy_norealloc", duration, n);
}

void bench_strcpy() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    char s[1024];

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        strcpy(s, t);
    }
    duration = BENCH_DURATION(start);

    bench_print("strcpy", duration, n);
}

void bench_strncpy() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    char s[1024];

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        strncpy(s, t, sizeof(s));
    }
    duration = BENCH_DURATION(start);

    bench_print("strncpy", duration, n);
}



void bench_strcat() {
    size_t n = 1000;
    size_t i;
    bench_ns_t start, duration;

    char s[327680];

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        strcat(s, t);
    }
    duration = BENCH_DURATION(start);
   
    bench_print("strcat", duration, n);
}

void bench_cstring_cat() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, 1024, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_cat(&s, t);
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);
    
    bench_print("cstring_cat", duration, n);
}

void bench_cstring_cat_norealloc() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, sizeof(t) * n + 10, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_cat(&s, t);
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);
    
    bench_print("cstring_cat_norealloc", duration, n);
}

void bench_cstring_uncat_norealloc() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, sizeof(t) * n + 10, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_uncat(&s, t, sizeof(t));
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);
    
    bench_print("cstring_uncat_norealloc", duration, n);
}

void bench_cstring_ncat_norealloc() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, sizeof(t) * n + 10, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_ncat(&s, t, sizeof(t));
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);
    
    bench_print("cstring_ncat_norealloc", duration, n);
}

void bench_cstring_lncat_norealloc() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, sizeof(t) * n + 10, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_lncat(&s, t, sizeof(t));
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);
    
    bench_print("cstring_lncat_norealloc", duration, n);
}

void bench_cstring_ulncat_norealloc() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, sizeof(t) * n + 10, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_ulncat(&s, t, sizeof(t));
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);
    
    bench_print("cstring_ulncat_norealloc", duration, n);
}

void bench_cstring_ll_cat_norealloc_min() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, CSTRING_LLSTR_SIZE * n + 10, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_ll_cat(&s, 0LL);
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);
    
    bench_print("cstring_ll_cat_norealloc min", duration, n);
}

void bench_cstring_ll_cat_norealloc_max() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, CSTRING_LLSTR_SIZE * n + 10, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_ll_cat(&s, LLONG_MAX);
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);

    bench_print("cstring_ll_cat_norealloc max", duration, n);
}

void bench_cstring_ll_ucat_norealloc_min() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, CSTRING_LLSTR_SIZE * n + 10, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_ll_ucat(&s, 0LL);
    }
    duration = BENCH_DURATION(start);

    cstring_free(&s);

    bench_print("cstring_ll_ucat_norealloc min", duration, n);
}

void bench_cstring_ll_ucat_norealloc_max() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, CSTRING_LLSTR_SIZE * n + 10, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_ll_ucat(&s, ULLONG_MAX);
    }
    duration = BENCH_DURATION(start);
    
    cstring_free(&s);

    bench_print("cstring_ll_ucat_norealloc max", duration, n);
}

void bench_sprintf() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    char buf[900000];

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        sprintf(buf, "%lld %d %s", 0LL, 100, "test");
    }
    duration = BENCH_DURATION(start);

    bench_print("sprintf", duration, n);
}

void bench_snprintf() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    char buf[900000];

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        snprintf(buf, sizeof(buf), "%lld %d %s", 0LL, 100, "test");
    }
    duration = BENCH_DURATION(start);

    bench_print("snprintf", duration, n);
}

void bench_cstring_printf_cat_realloc() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, (CSTRING_LLSTR_SIZE * 2 + 10) * n, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_printf_cat(&s, "%lld %d %s", 0LL, 100, "test");
    }
    duration = BENCH_DURATION(start);
    
    cstring_free(&s);

    bench_print("cstring_printf_cat_norealloc", duration, n);
}

void bench_cstring_nprintf_cat() {
    size_t n = 10000;
    size_t i;
    bench_ns_t start, duration;

    cstring_t s;
    cstring_init(&s, (CSTRING_LLSTR_SIZE * 2 + 10) * n, NULL);

    start = BENCH_START();
    for (i = 0; i < n; i++) {
        cstring_nprintf_cat(&s, "%lld %d %s", 0LL, 100, "test");
    }
    duration = BENCH_DURATION(start);
    
    cstring_free(&s);

    bench_print("cstring_nprintf_cat", duration, n);
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
    c_allocator_default_init(); /* init default allocator */

    bench_burn();

    bench_strcpy();
    bench_strncpy();

    bench_cstring_cpy_norealloc();
    bench_cstring_ucpy_norealloc();
    bench_cstring_uncpy_norealloc();
    bench_cstring_lncpy_norealloc();
    bench_cstring_ulncpy_norealloc();

    printf("\n");

    bench_strcat();

    bench_cstring_cat();
    bench_cstring_cat_norealloc();
    bench_cstring_ncat_norealloc();
    bench_cstring_uncat_norealloc();
    bench_cstring_lncat_norealloc();
    bench_cstring_ulncat_norealloc();

    printf("\n");

    bench_cstring_ll_ucat_norealloc_min();
    bench_cstring_ll_cat_norealloc_min();

    printf("\n");

    bench_cstring_ll_ucat_norealloc_max();
    bench_cstring_ll_cat_norealloc_max();

    printf("\n");

    bench_sprintf();
    bench_snprintf();
    bench_cstring_nprintf_cat();
    bench_cstring_printf_cat_realloc();

    return 0;
}
