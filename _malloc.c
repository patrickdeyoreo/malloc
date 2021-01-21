#include <error.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include "malloc.h"

/**
 * _malloc_sbrk - extend the program break to allocate memory
 *
 * @size: size to allocate
 * @chunk: pointer to the start of the chunk
 * @unused: number of unused allocated bytes
 *
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer to the start of the allocated memory region.
 */
static void *_malloc_sbrk(size_t size, void *chunk, size_t unused)
{
	chunk_header_t *header = chunk;
	long page_size = sysconf(_SC_PAGESIZE);
	size_t n_pages =
		((size + sizeof(*header) * 2 - unused - 1) / page_size) + 1;

	errno = 0;
	if (sbrk(page_size * n_pages) == (void *) -1 && errno == ENOMEM)
	{
		error(0, ENOMEM, NULL);
		return (NULL);
	}
	header->prev_size = 0;
	header->size = page_size * n_pages + unused;
	return (chunk);
}


/**
 * _malloc - dynamically allocate heap memory
 *
 * @size: size to allocate
 *
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer to the start of the allocated memory region.
 */
void *_malloc(size_t size)
{
	static void *start;
	void *chunk = start;
	chunk_header_t *header = chunk;
	size_t unused = 0;

	if (start)
	{
		while (CHUNK_USED(header))
			header = chunk = (char *) chunk + CHUNK_SIZE(header);
		unused = CHUNK_SIZE(header);
	}
	else
	{
		chunk = start = sbrk(0);
	}
	if (unused < size + PADDING(size) + sizeof(*header) * 2)
		chunk = _malloc_sbrk(size + PADDING(size), chunk, unused);
	if (!chunk)
		return (NULL);
	header = chunk;
	unused = CHUNK_SIZE(header);
	header->size = size + PADDING(size) + sizeof(*header);
	((chunk_header_t *) ((char *) chunk + CHUNK_SIZE(header)))->size =
		unused - CHUNK_SIZE(header);
	CHUNK_SET_USED(header);
	return ((char *) chunk + sizeof(*header));
}
