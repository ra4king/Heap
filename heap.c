#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

struct heap_t {
	compare_func compare;
	void** data;
	int size;
	int capacity;
};

#define INITIAL_SIZE 10

struct heap_t* heap_create(compare_func compare) {
	struct heap_t* heap = malloc(sizeof(struct heap_t));
	if(!heap)
		return NULL;

	heap->data = malloc(INITIAL_SIZE * sizeof(void*));
	if(!heap->data) {
		free(heap);
		return NULL;
	}

	heap->compare = compare;
	heap->size = 0;
	heap->capacity = INITIAL_SIZE;

	return heap;
}

static int resize_heap(struct heap_t* heap) {
	unsigned int newCap = heap->capacity * 3 / 2;
	printf("Resizing heap: current capacity: %d, new capacity: %d\n", heap->capacity, newCap);
	heap->data = realloc(heap->data, newCap * sizeof(void*));
	if(!heap->data) {
		printf("What in the hell happened... realloc failed?!\n");
		return -1;
	}

	heap->capacity = newCap;
	return 0;
}

int heap_insert(struct heap_t* heap, void* elem) {
	if(!elem)
		return -1;

	if(heap->size == heap->capacity)
		if(resize_heap(heap) == -1)
			return -1;

	int pos = heap->size++;

	int prevPos = pos;
	while(pos && heap->compare(elem, heap->data[(pos / 2) + ((pos & 0x1) - 1)]) < 0) {
		pos = (pos / 2) + ((pos & 0x1) - 1);
		heap->data[prevPos] = heap->data[pos];
		prevPos = pos;
	}

	heap->data[pos] = elem;

	return 0;
}

void* heap_peek(struct heap_t* heap) {
	return heap->size ? heap->data[0] : NULL;
}

void* heap_pop(struct heap_t* heap) {
	if(!heap->size)
		return NULL;

	void* elem = heap->data[0];
	void* lostElem = heap->data[0] = heap->data[--heap->size];

	int pos = 0;
	while(1) {
		int compLeft = 0;
		if(pos * 2 + 1 < heap->size)
			compLeft = heap->compare(lostElem, heap->data[pos * 2 + 1]);

		int compRight = 0;
		if(pos * 2 + 2 < heap->size)
			compRight = heap->compare(lostElem, heap->data[pos * 2 + 2]);

		if(compLeft <= 0 && compRight <= 0)
			break;

		if(compRight <= 0 || compLeft > compRight) {
			heap->data[pos] = heap->data[pos * 2 + 1];
			pos = pos * 2 + 1;
		}
		else {
			heap->data[pos] = heap->data[pos * 2 + 2];
			pos = pos * 2 + 2;
		}
	}

	heap->data[pos] = lostElem;

	return elem;
}

int heap_size(struct heap_t* heap) {
	return heap->size;
}

void heap_delete(struct heap_t* heap, free_func free_f) {
	for(int i = 0; i < heap->size; i++) {
		free_f(heap->data[i]);
	}

	free(heap->data);
	free(heap);
}
