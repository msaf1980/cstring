#ifndef _CSTRING_H_
#define _CSTRING_H_

#include <cstring/allocator.h>

#include <ctype.h>
#include <stdarg.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  size_t size;
  size_t capacity;
  c_allocator_t *allocator;
  char *data;
} cstring_t;

/* 
 * Init empthy string with pre-allocated capacity.
 * 
 * Maximum string size is capacity (without terminated symbol '\0').
 * 
 * @s ctring pointer
 * 
 * @capacity Capacity (without reserverd termination symbol). Really allocated (capacity + 1) for terminated symbol.
 * 
 * @a Allocator.
 *    If NULL, default allocator used (malloc/free). Init it with c_allocator_default_init() once at programm start
 * 
 * @return -1 on error
 */
int cstring_init(cstring_t *s, size_t capacity, c_allocator_t *a);
/* 
 * Attach null-terminated string.
 * 
 * Maximum string size is capacity (without terminated symbol '\0').
 * 
 * @s ctring pointer
 *
 * @size     Buffer size (like strlen)
 * 
 * @capacity Buffer capacity. Internal cstring capacity set to (capacity - 1).
 * 
 * @a Allocator.
 *    If NULL, default allocator used. Init it with c_allocator_default_init() once at programm start
 * 
 * @return -1 on error  */
void cstring_attach(cstring_t *s, char *buf, size_t size, size_t capacity, c_allocator_t *a);
/* 
 * Free string
 */
static inline void cstring_free(cstring_t *s) {
  if (s->allocator && s->allocator->free_func)
    s->allocator->free_func(s->data);
  s->data = NULL;
  s->size = 0;
  s->capacity = 0;
}
/* Reserve capacity for string (really allocated (capacity + 1) for terminated symbol) */
int cstring_reserve(cstring_t *s, size_t capacity);
/* Truncate string */
char *cstring_trunc(cstring_t *s, size_t size);
/* Copy string with reallocate
 * 
 * @return Return 0 on success or -1 on error */
char *cstring_cpy(cstring_t *s, const char *src);
/* Copy string without bound checking and reallocate (DANGEROUS) */
char *cstring_ucpy(cstring_t *s, const char *src);
/* Copy n symbols from string with reallocate (if source string is smaller, all symbols copied) */
char *cstring_ncpy(cstring_t *s, const char *src, size_t n);
/* Copy n symbols from string without bound checking and reallocate (DANGEROUS) (if source string is smaller, all symbols copied) */
char *cstring_uncpy(cstring_t *s, const char *src, size_t n);
/* Copy string with reallocate (at most n bytes copied) */
char *cstring_lncpy(cstring_t *s, const char *src, size_t n);
/* Copy string without bounds checking (at most n bytes copied) (DANGEROUS) */
char *cstring_ulncpy(cstring_t *s, const char *src, size_t n);

/* Append to string with reallocate */
char *cstring_cat(cstring_t *s, const char *src);


 /* Append n symbols from string with reallocate (if source string is smaller, all symbols copied) */
 char *cstring_ncat(cstring_t *s, const char *src, size_t n);
/* Append n symbols from string without bound checking and reallocate (if source string is smaller, all symbols copied) (DANGEROUS) */
char *cstring_uncat(cstring_t *s, const char *src, size_t n);
/* Append string with reallocate (at most n bytes copied) */
char *cstring_lncat(cstring_t *s, const char *src, size_t n);
/* Append string without bound checking and reallocate (at most n bytes copied) (DANGEROUS) */
char *cstring_ulncat(cstring_t *s, const char *src, size_t n);


/* Unsigned long long number representation without bound checking and reallocate (DANGEROUS) */
char *cstring_ll_u(cstring_t *s, long long v);
/* Unsigned long long number representation with reallocate */
char *cstring_ll(cstring_t *s, long long v);
/* Append unsigned long long number representation without bound checking and reallocate (DANGEROUS) */
char *cstring_ll_ucat(cstring_t *s, long long v);
/* Append unsigned long long number representation with reallocate */
char *cstring_ll_cat(cstring_t *s, long long v);


/* Append string (vsprintf-like formated) with reallocate, on error return negative value */
ssize_t cstring_vprintf_cat(cstring_t *s, const char *fmt, va_list ap);
/* Append string (sprintf-like formated) with reallocate, on error return negative value */
ssize_t cstring_printf_cat(cstring_t *s, const char *fmt, ...);
/* Append string (vsnprintf-like formated) without reallocate. */
ssize_t cstring_vnprintf_cat(cstring_t *s, const char *fmt, va_list ap);
/* 
 * Append string (snprintf-like formated) without reallocate.
 * 
 * @return On error - negative value. 
 * 
 * If the output was truncated due to capacity overflow, return value is the number of characters needed for buffer
 */
ssize_t cstring_nprintf_cat(cstring_t *s, const char *fmt, ...);


/* Trim from left and from right of string chars in set */
char *cstring_trim(cstring_t *s, const char *cset);
/* Trim from right of string chars in set */
char *cstring_rtrim(cstring_t *s, const char *cset);
/* Trim from left right of string chars in set */
char *cstring_ltrim(cstring_t *s, const char *cset);


/* Insert (sze) symbols to string position from char buffer */
char *cstring_insert(cstring_t *s, size_t pos, const char *si, const size_t sze);


/* Apply toupper() to every character of the sds string 's'. */
char *cstring_upper(cstring_t *s);
/* Apply toupper_l() to every character of the sds string 's'. */
char *cstring_upper_l(cstring_t *s, locale_t locale);
/* Apply tolower() to every character of the sds string 's'. */
char *cstring_lower(cstring_t *s);
/* Apply tolower_l() to every character of the sds string 's'. */
char *cstring_lower_l(cstring_t *s, locale_t locale);

#ifdef __cplusplus
}
#endif

#endif /* _CSTRING_H_ */
