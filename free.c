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

	if (!ptr)
		return;
	header = (char *) ptr - sizeof(*header);
	CHUNK_UNSET_USED(header);
	((chunk_header_t *) ((char *) ptr + CHUNK_SIZE(header)))->prev =
		CHUNK_SIZE(header);
}
