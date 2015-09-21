#ifndef __HEAP_H__
#define __HEAP_H__

struct heap_t;

typedef int (*compare_func)(void*, void*);

/*
Frees the resource
*/
typedef void (*free_func)(void*);

struct heap_t* create_heap(compare_func comp);

/*
Returns 0 on success, -1 on failure
*/
int insert(struct heap_t* heap, void* elem);

void* peek(struct heap_t* heap);

void* pop(struct heap_t* heap);

int size(struct heap_t* heap);

void** get_data(struct heap_t* heap);

void delete_heap(struct heap_t* heap, free_func free_f);

#endif
