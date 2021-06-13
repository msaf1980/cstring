#include <cstring/cstring.h>
#include <cstring/number.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define CAPACITY_WITH_FACTOR(n) ( (n > 64) ? ( (n * 15 / 640 + 1) * 64 ) : 64 ) /* size with realloc factor */

int cstring_init(cstring_t *s, size_t capacity, c_allocator_t *a) {
    s->data = NULL;
    s->size = 0;
    s->capacity = 0;

    if (a) {
        s->allocator = a;
    } else {
        s->allocator = &c_allocator_default;
    }

    return cstring_reserve(s, capacity);
}

void cstring_attach(cstring_t *s, char *buf, size_t size, size_t capacity, c_allocator_t *a) {
    if (a) {
        s->allocator = a;
    } else {
        s->allocator = &c_allocator_default;
    }
    if (buf && capacity > 0) {
        s->data = buf;
        s->size = size;
        s->capacity = capacity-1;
    } else {
        s->data = NULL;
        s->size = 0;
        s->capacity = 0;
    }
}

int cstring_reserve(cstring_t *s, size_t capacity) {
    if (s->allocator == NULL || s->allocator->alloc_func == NULL || s->allocator->free_func == NULL)
        return -1;    
    if (capacity == 0) {
        cstring_free(s);
    } else {
        char *p;
        p = (char *) s->allocator->alloc_func(sizeof(char) * (capacity + 1));
        if (p) {
            if (s->size > 0) {
                if (s->size >= capacity) {
                    s->size = capacity;
                }
                memcpy(p, s->data, sizeof(char) * s->size);
            }
            s->capacity = capacity;
            p[s->size] = '\0';
            s->allocator->free_func(s->data);
            s->data = p;
        } else {
            return -1;
        }
    }
    return 0;
}

char *cstring_trunc(cstring_t *s, size_t size) {
    if (s->size > size) {
        s->data[size] = '\0';
        s->size = size;
    }

    return s->data;
}

inline __attribute__((always_inline)) char *cstring_uncpy(cstring_t *s, const char *src, size_t n) {
    memcpy(s->data, src, n * sizeof(char));
    s->data[n] = '\0';
    s->size = n;

    return s->data;
}

inline __attribute__((always_inline)) char *cstring_ulncpy(cstring_t *s, const char *src, size_t n) {
    char *p = memccpy(s->data, src, '\0', n * sizeof(char));
    if (p) {
        n = p - s->data - 1;
    }
    s->data[n] = '\0';
    s->size = n;

    return s->data;
}

char *cstring_lncpy(cstring_t *s, const char *src, size_t n) {
    if (src == NULL)
        return s->data;
        
    if (s->capacity == 0 || s->capacity < n) {
        if (cstring_reserve(s, CAPACITY_WITH_FACTOR(n)) == -1) {
            return NULL;
        }
    }

    return cstring_ulncpy(s, src, n);
}

char *cstring_ncpy(cstring_t *s, const char *src, size_t n) {
    if (src == NULL)
        return s->data;

    size_t l = strlen(src);
    if (l < n) {
        n = l;
    }

    if (s->capacity == 0 || s->capacity < n) {
        if (cstring_reserve(s, CAPACITY_WITH_FACTOR(n)) == -1) {
            return NULL;
        }
    }

    return cstring_uncpy(s, src, n);
}

char *cstring_cpy(cstring_t *s, const char *src) {
    size_t n;
    if (src == NULL)
        return s->data;

    n = strlen(src);

    if (s->capacity == 0 || s->capacity < n) {
        if (cstring_reserve(s, CAPACITY_WITH_FACTOR(n)) == -1) {
            return NULL;
        }
    }

    return cstring_uncpy(s, src, n);
}


char *cstring_ucpy(cstring_t *s, const char *src) {
    size_t n = strlen(src);
    return cstring_uncpy(s, src, n);
}

inline __attribute__((always_inline)) char *cstring_uncat(cstring_t *s, const char *src, size_t n) {
    memcpy(s->data + s->size, src, n * sizeof(char));
    s->size += n;
    s->data[s->size] = '\0';

    return s->data;
}

char *cstring_ncat(cstring_t *s, const char *src, size_t n) {
    size_t new_size;
    size_t l;
    if (src == NULL)
        return s->data;
    l = strlen(src);
    if (l < n) {
        n = l;
    }

    new_size = s->size + n;
    if (s->capacity == 0 || s->capacity < new_size) {
        if (cstring_reserve(s, CAPACITY_WITH_FACTOR(new_size)) == -1) {
            return NULL;
        }
    }

    return cstring_uncat(s, src, n);
}

char *cstring_cat(cstring_t *s, const char *src) {
    size_t new_size;
    size_t n;
    if (src == NULL)
        return s->data;
    n = strlen(src);

    new_size = s->size + n;
    if (s->capacity == 0 || s->capacity < new_size) {
        if (cstring_reserve(s, CAPACITY_WITH_FACTOR(new_size)) == -1) {
            return NULL;
        }
    }

    return cstring_uncat(s, src, n);
}

char *cstring_ulncat(cstring_t *s, const char *src, size_t n) {
   char *p = memccpy(s->data + s->size, src, '\0', n * sizeof(char));
    if (p) {
        s->size = p - s->data - 1;
    } else {
        s->size += n;
    }
    s->data[s->size] = '\0';

    return s->data;
}

char *cstring_lncat(cstring_t *s, const char *src, size_t n) {
    size_t new_size = s->size + n;
    if (src == NULL)
        return s->data;

    if (s->capacity == 0 || s->capacity < new_size) {
        if (cstring_reserve(s, CAPACITY_WITH_FACTOR(new_size)) == -1) {
            return NULL;
        }
    }

    return cstring_ulncat(s, src, n);
}

inline __attribute__((always_inline)) char *cstring_ll_u(cstring_t *s, long long v) {
    s->size = cstring_ll2str(s->data, v);
    return s->data;
}

char *cstring_ll(cstring_t *s, long long v) {
    size_t n;
    if (s->capacity == 0 || s->capacity < CSTRING_LLSTR_SIZE) {
        if (cstring_reserve(s, CAPACITY_WITH_FACTOR(CSTRING_LLSTR_SIZE)) == -1) {
            return NULL;
        }
    }

    return cstring_ll_u(s, v);
}

inline __attribute__((always_inline)) char *cstring_ll_ucat(cstring_t *s, long long v) {
    s->size += cstring_ll2str(s->data + s->size, v);
    return s->data;
}

char *cstring_ll_cat(cstring_t *s, long long v) {
    size_t new_size = s->size + CSTRING_LLSTR_SIZE;
    if (s->capacity == 0 || s->capacity < new_size) {
        if (cstring_reserve(s, CAPACITY_WITH_FACTOR(new_size)) == -1) {
            return NULL;
        }
    }

    return cstring_ll_ucat(s, v);
}

ssize_t cstring_vprintf_cat(cstring_t *s, const char *fmt, va_list ap) {
    va_list cpy;
    char staticbuf[1024], *buf = staticbuf, *t;
    size_t buflen = strlen(fmt) * 2;
    size_t new_size;
    ssize_t n;
    char *p;

    /* We try to start using a static buffer for speed.
     * If not possible we revert to heap allocation. */
    if (buflen > sizeof(staticbuf)) {
        buf = s->allocator->alloc_func(buflen);
        if (buf == NULL) return -1;
    } else {
        buflen = sizeof(staticbuf);
    }

    /* Try with buffers two times bigger every time we fail to
     * fit the string in the current buffer size. */
    while(1) {
        va_copy(cpy,ap);
        n = vsnprintf(buf, buflen, fmt, cpy);
        va_end(cpy);
        if (n < 0) return n;
        if (n >= buflen) {
            if (buf != staticbuf) s->allocator->free_func(buf);
            buflen = n+1;
            buf = s->allocator->alloc_func(buflen);
            if (buf == NULL) return -1;
            continue;
        }
        break;
    }

    new_size = s->size + n;
    if (s->capacity == 0 || s->capacity < new_size) {
        if (cstring_reserve(s, CAPACITY_WITH_FACTOR(new_size)) == -1) {
            return -1;
        }
    }

    (void) cstring_uncat(s, buf, n);
    if (buf != staticbuf) s->allocator->free_func(buf);
    return s->size;
}

ssize_t cstring_printf_cat(cstring_t *s, const char *fmt, ...) {
    ssize_t n;
    va_list ap;
    
    va_start(ap, fmt);
    n = cstring_vprintf_cat(s, fmt, ap);
    va_end(ap);
    return n;
}

ssize_t cstring_vnprintf_cat(cstring_t *s, const char *fmt, va_list ap) {
    ssize_t blen = s->capacity-s->size;
    int n = vsnprintf(s->data+s->size, blen+1, fmt, ap);
    if (n < 0) {
        return n;
    } else if (n > blen) {
        ssize_t pre_size = s->size;
        s->size = s->capacity;
        return pre_size + n;
    } else
        return s->size += n;
}

ssize_t cstring_nprintf_cat(cstring_t *s, const char *fmt, ...) {
    ssize_t n;
    va_list ap;
    
    va_start(ap, fmt);
    n = cstring_vnprintf_cat(s, fmt, ap);
    va_end(ap);
    return n;
}

char *cstring_trim(cstring_t *s, const char *cset) {
    char *sp, *ep;
    size_t len;

    if (s->size == 0 || cset == NULL) return NULL;

    sp = s->data;
    ep = s->data+s->size-1;
    while(sp <= ep && strchr(cset, *sp)) sp++;
    while(ep > sp && strchr(cset, *ep)) ep--;
    len = (sp > ep) ? 0 : ((ep-sp)+1);
    if (len != s->size) {
        if (s->data != sp) memmove(s->data, sp, len);
        s->data[len] = '\0';
        s->size = len;
    }
    return s->data;
}

char *cstring_rtrim(cstring_t *s, const char *cset) {
    char *sp, *ep;
    size_t len;

    if (s->size == 0 || cset == NULL) return NULL;

    sp = s->data;
    ep = s->data+s->size-1;
    while(ep > sp && strchr(cset, *ep)) ep--;
    len = (sp > ep) ? 0 : ((ep-sp)+1);
    if (len != s->size) {
        s->data[len] = '\0';
        s->size = len;
    }
    return s->data;
}

char *cstring_ltrim(cstring_t *s, const char *cset) {
    char *sp, *ep;
    size_t len;

    if (s->size == 0 || cset == NULL) return NULL;

    sp = s->data;
    ep = s->data+s->size-1;
    while(sp <= ep && strchr(cset, *sp)) sp++;
    len = (sp > ep) ? 0 : ((ep-sp)+1);
    if (len != s->size) {
        if (s->data != sp) memmove(s->data, sp, len);
        s->data[len] = '\0';
        s->size = len;
    }
    return s->data;
}
