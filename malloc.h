#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stddef.h>

/**
 * struct chunk_s - malloc chunk header
 *
 * @prev_size: size of the previous chunk
 * @size: size of the chunk
 */
typedef struct chunk_s
{
	size_t prev_size;
	size_t size;
} chunk_t;

void *naive_malloc(size_t size);
void *_malloc(size_t size);
void *_calloc(size_t nmemb, size_t size);
void *_realloc(void *ptr, size_t size);
void _free(void *ptr);

#endif /* _MALLOC_H_ */
