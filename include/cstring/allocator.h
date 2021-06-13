#ifndef _CSTRING_ALLOCATOR_H_
#define _CSTRING_ALLOCATOR_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct c_allocator_t_ {
    void *(*alloc_func)(size_t);
    void (*free_func)(void*);
} c_allocator_t;


/* default allocator. If used, init it with c_allocator_default_init() once at programm start */
extern c_allocator_t c_allocator_default;
/* nope allocator. If used, init it with c_allocator_default_init() once at programm start */
extern c_allocator_t c_allocator_none;
/* init default allocators */
void c_allocator_default_init();

/* init allocator with custom functions (malloc/realloc/free) */
void c_allocator_init(c_allocator_t *c, void *(*alloc_func)(size_t), void (*free_func)(void*));

#ifdef __cplusplus
}
#endif

#endif /* _CSTRING_ALLOCATOR_H_ */
