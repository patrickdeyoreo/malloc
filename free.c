#include <error.h>
#include <errno.h>
#include <unistd.h>

#include "malloc.h"

/**
 * _free - deallocate memory allocated with the _malloc family of functions
 *
 * @ptr: pointer to a memory region returned by _malloc, _calloc or _realloc
 */
void _free(void *ptr)
{
	chunk_header_t *header = NULL;
	size_t size = 0;

	if (ptr)
	{
		header = (chunk_header_t *) (char *) ptr - sizeof(*header);
		CHUNK_SET_FREE(header);
		size = CHUNK_GET_SIZE(header);
		header = (chunk_header_t *) ((char *) header + size);
		CHUNK_SET_PREV(header, size);
	}
}
