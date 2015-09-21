#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "heap.h"

int compare(void* a, void* b) {
	return (intptr_t)a - (intptr_t)b;
}

int main() {
	struct heap_t* heap = create_heap(compare);

	insert(heap, (void*)4);
	insert(heap, (void*)5);
	insert(heap, (void*)10);
	insert(heap, (void*)1);
	insert(heap, (void*)-5);
	insert(heap, (void*)7);
	insert(heap, (void*)10);
	insert(heap, (void*)100);
	insert(heap, (void*)42);
	insert(heap, (void*)6);
	insert(heap, (void*)2);;
	insert(heap, (void*)-10);
	insert(heap, (void*)34);
	insert(heap, (void*)50);

	printf("Heap size: %d\n", size(heap));

	printf("\nPopping elements:\n");

	while(size(heap)) {
		printf("Next element: %ld\n", (intptr_t)pop(heap));
	}

	delete_heap(heap, free);

	return 0;
}
