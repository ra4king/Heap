#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "heap.h"

struct myfancystruct_t {
	int value;
	int specialvalue1;
	int specialvalue2;
	int specialvalue3;
};

void initialize_fancy(struct myfancystruct_t* fancy, int value) {
	fancy->value = value;
	fancy->specialvalue1 = fancy->value * 5;
	fancy->specialvalue2 = fancy->specialvalue1 >> 2;
	fancy->specialvalue3 = fancy->specialvalue2 & 0x5353;
}

int check_fancy(struct myfancystruct_t* fancy) {
	struct myfancystruct_t clone;
	initialize_fancy(&clone, fancy->value);
	if(clone.specialvalue1 != fancy->specialvalue1)
		return 0;
	if(clone.specialvalue2 != fancy->specialvalue2)
		return 0;
	if(clone.specialvalue3 != fancy->specialvalue3)
		return 0;

	return 1;
}

int compare(void* a, void* b) {
	return ((struct myfancystruct_t*)a)->value - ((struct myfancystruct_t*)b)->value;
}

int main() {
	struct heap_t* heap = heap_create(compare);

	printf("Adding values...");

	srand((unsigned int)time(NULL));
	for(int i = 0; i < 10000; i++) {
		struct myfancystruct_t* fancy = malloc(sizeof(struct myfancystruct_t));
		initialize_fancy(fancy, rand());
		heap_insert(heap, fancy);
	}

	printf("Heap size: %d\n", heap_size(heap));

	printf("\nPopping elements:\n");

	while(heap_size(heap)) {
		struct myfancystruct_t* fancy = heap_pop(heap);

		printf("Next element: %d", fancy->value);

		if(!check_fancy(fancy)) {
			printf(" - INVALID FANCY!");
		}

		printf("\n");

		free(fancy);
	}

	printf("\nMore random testing...\n");

	for(int i = 0; i < 100000; i++) {
		if((i / 10) % 3 != 0) {
			struct myfancystruct_t* fancy = malloc(sizeof(struct myfancystruct_t));
			initialize_fancy(fancy, rand());
			heap_insert(heap, fancy);
		}
		else {
			struct myfancystruct_t* fancy = heap_pop(heap);

			if(!fancy) {
				printf("Pop returned NULL, heap size: %d\n", heap_size(heap));
			}
			else if(!check_fancy(fancy)) {
				printf("INVALID FANCY!\n");
			}

			free(fancy);
		}
	}

	while(heap_size(heap)) {
		struct myfancystruct_t* fancy = heap_pop(heap);
		if(!check_fancy(fancy)) {
			printf("INVALID FANCY!\n");
		}
		free(fancy);
	}

	printf("SUCCESS!\n");

	heap_delete(heap, free);

	return 0;
}
