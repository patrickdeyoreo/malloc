#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stddef.h>

#define ALIGNMENT sizeof(void *)
#define PADDING(size) (-(size) & (ALIGNMENT - 1))
#define CHUNK_SIZE(chunk_header_ptr) ((chunk_header_ptr)->size & ~1UL)
#define CHUNK_USED(chunk_header_ptr) ((chunk_header_ptr)->size & 1)
#define CHUNK_SET_USED(chunk_header_ptr) ((chunk_header_ptr)->size |= 1)
#define CHUNK_UNSET_USED(chunk_header_ptr) ((chunk_header_ptr)->size &= ~1UL)
#define CHUNK_TOGGLE_USED(chunk_header_ptr) ((chunk_header_ptr)->size ^= 1)

/**
 * struct chunk_header_s - malloc chunk header
 *
 * @prev_size: size of the previous chunk
 * @size: size of the chunk
 */
typedef struct chunk_header_s
{
	size_t prev_size;
	size_t size;
} chunk_header_t;

void *naive_malloc(size_t size);
void *_malloc(size_t size);
void *_calloc(size_t nmemb, size_t size);
void *_realloc(void *ptr, size_t size);
void _free(void *ptr);

#endif /* _MALLOC_H_ */
