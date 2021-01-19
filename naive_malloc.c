#include <error.h>
#include <errno.h>
#include <unistd.h>

#include "malloc.h"

/**
 * naive_malloc - extend the program break to dynamically allocate memory
 *
 * @size: size to allocate
 *
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer to the start of the allocated memory region.
 */
void *naive_malloc(size_t size)
{
	static void *start;
	static size_t n_chunks;
	unsigned char *chunk = NULL;
	size_t unused_size = 0;
	size_t chunk_index = 0;
	long page_size = 0;

	if (n_chunks)
	{
		for (chunk = start; chunk_index < n_chunks; ++chunk_index)
			chunk += *((size_t *)chunk);
		unused_size = *((size_t *)chunk);
	}
	else
	{
		page_size = sysconf(_SC_PAGESIZE);
		start = sbrk(0);
		errno = 0;
		if (sbrk(page_size) == (void *) -1 && errno == ENOMEM)
		{
			error(0, ENOMEM, NULL);
			return (NULL);
		}
		chunk = start;
		unused_size = page_size;
	}
	n_chunks += 1;
	*((size_t *)chunk) = size;
	*((size_t *)chunk + size) = unused_size - size;
	return (chunk + sizeof(size_t));
}
