#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "heap.h"

int compare(void* a, void* b) {
	return (intptr_t)a - (intptr_t)b;
}

int main() {
	struct heap_t* heap = heap_create(compare);

	printf("Adding values...");
	
	srand((unsigned int)time(NULL));
	for(int i = 0; i < 100; i++) {
		heap_insert(heap, (void*)(intptr_t)rand());
	}

	printf("Heap size: %d\n", heap_size(heap));

	printf("\nPopping elements:\n");

	intptr_t prev = -1;
	while(heap_size(heap)) {
		intptr_t value = (intptr_t)heap_pop(heap);

		printf("Next element: %ld", value);

		if(prev != -1 && value < prev) {
			printf(" - OUT OF ORDER!!!\n");
		}
		else {
			printf("\n");
		}

		prev = value;
	}

	heap_delete(heap, free);

	return 0;
}
