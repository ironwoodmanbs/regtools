/* array.c */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

struct array_header {
	unsigned int count;
	unsigned int size;
};

void* array_new(unsigned int count, unsigned int size) {
	unsigned int need_size = count * size + sizeof(struct array_header);
	struct array_header* header = malloc(need_size);
	if(header == NULL) return NULL;
	header->count = count;
	header->size = size;
	return header + 1;
};

void array_free(void* array) {
	struct array_header* header = (struct array_header*)array - 1;
	free((void*)header);
};
	
unsigned int array_count(void* array) {
	struct array_header* header = (struct array_header*)array - 1;
	return header->count;
};

void* array_add(void* array, unsigned int number, unsigned int count) {
	struct array_header* header = (struct array_header*)array - 1;
	if(number > header->count){
		perror("Fault in arguments of array_add function");
		exit(EXIT_FAILURE);
	};
	unsigned int need_size = (count + header->count) * header->size + sizeof(struct array_header);
	header = realloc(header, need_size);
	if(header == NULL) return NULL;
	void* src = (void*)((uintptr_t)(header + 1) + (header->size * number));
	void* dest = (void*)((uintptr_t)src + (header->size * count));
	unsigned int elements = header->count - number;
	memmove(dest, src, header->size * elements);
	header->count += count;
	return header + 1;
};

void* array_cut(void* array, unsigned int number, unsigned int count) {
	struct array_header* header = (struct array_header*)array - 1;
	if(number + count > header->count) {
		perror("Fault in arguments of array_cut function");
		exit(EXIT_FAILURE);
	};
	void* dest = (void*)((uintptr_t)array + (header->size * number));
	void* src = (void*)((uintptr_t)dest + (header->size * count));
	memcpy(dest, src, header->size * (header->count - number));
	header->count = header->count - count;
	unsigned int need_size = header->count * header->size + sizeof(struct array_header);
	header = realloc(header, need_size);
	if(header == NULL) return NULL;
	return header + 1;
};
