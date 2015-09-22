#ifndef __HEAP_H__
#define __HEAP_H__

struct heap_t;

typedef int (*compare_func)(void*, void*);

/*
Frees the resource
*/
typedef void (*free_func)(void*);

struct heap_t* heap_create(compare_func comp);

/*
Returns 0 on success, -1 on failure
*/
int heap_insert(struct heap_t* heap, void* elem);

void* heap_peek(struct heap_t* heap);

void* heap_pop(struct heap_t* heap);

int heap_size(struct heap_t* heap);

void heap_delete(struct heap_t* heap, free_func free_f);

#endif
