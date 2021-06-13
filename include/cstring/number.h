#ifndef __NUMBER_H__
#define __NUMBER_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CSTRING_LLSTR_SIZE 21
/* Long long number -> string conversion.
 * 's' must point to a string with room for at least SDS_LLSTR_SIZE bytes.
 * The function returns the length of the null-terminated string
 * representation stored at 's'. */
size_t cstring_ll2str(char *s, long long value);
/* Identical cstring_ll2str, but for unsigned long long type. */
size_t cstring_ull2str(char *s,  unsigned long long value);

#ifdef __cplusplus
}
#endif


#endif // __NUMBER_H__