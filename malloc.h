#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stddef.h>

#define ALIGNMENT sizeof(void *)
#define PADDING(n) (-(n) & (ALIGNMENT - 1))
#define CHUNK_GET_SIZE(p) ((p)->size & ~1UL)
#define CHUNK_GET_PREV(p) ((p)->prev)
#define CHUNK_GET_USED(p) ((p)->size & 1)
#define CHUNK_GET_FREE(p) ((p)->size & 1 ^ 1)
#define CHUNK_SET_SIZE(p, n) ((p)->size = (n) | ((p)->size & 1))
#define CHUNK_SET_PREV(p, n) ((p)->prev = (n))
#define CHUNK_SET_USED(p) ((p)->size |= 1)
#define CHUNK_SET_FREE(p) ((p)->size &= ~1UL)

/**
 * struct chunk_header_s - malloc chunk header
 *
 * @prev_size: size of the previous chunk
 * @size: size of the chunk
 */
typedef struct chunk_header_s
{
	size_t prev;
	size_t size;
} chunk_header_t;

void *naive_malloc(size_t size);
void *_malloc(size_t size);
void *_calloc(size_t nmemb, size_t size);
void *_realloc(void *ptr, size_t size);
void _free(void *ptr);

#endif /* _MALLOC_H_ */
