#include <cstring/allocator.h>

#include <stdlib.h>

c_allocator_t c_allocator_default;
c_allocator_t c_allocator_none;

void c_allocator_default_init() {
    c_allocator_default.alloc_func = malloc;
    c_allocator_default.free_func = free;

    c_allocator_none.alloc_func = NULL;
    c_allocator_none.free_func = NULL;
}

void c_allocator_init(c_allocator_t *c, void *(*alloc_func)(size_t), void (*free_func)(void*)) {
    c->alloc_func = alloc_func;
    c->free_func = free_func;
}
