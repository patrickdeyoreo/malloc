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
	void *start = sbrk(0);

	errno = 0;
	if (sbrk(size + sizeof(size_t)) == (void *) -1 && errno == ENOMEM)
	{
		error(0, errno, NULL);
		return (NULL);
	}
	*((size_t *) start) = size;
	return (start + sizeof(size_t));
}
