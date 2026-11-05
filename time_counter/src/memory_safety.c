#include "header.h"

#include <stdlib.h>
#include <inttypes.h>

void *smalloc(size_t size)
{
	if (size == 0)
	{
		fprintf(stderr, "Invalid allocation size (0) passed to smalloc() fn\n");
		exit(EXIT_FAILURE);
	}

	void *ptr = malloc(size);
	if (ptr == NULL)
	{
		fprintf(stderr, "error: malloc() failed to allocate memory of size %" PRIu64"\n", size);
		exit(EXIT_FAILURE);
	}
	return ptr;
}

void *srealloc(void *ptr, size_t size)
{
	if (size == 0)
	{
		fprintf(stderr, "Invalid allocation size (0) passed to srealloc() fn\n");
		exit(EXIT_FAILURE);
	}

	void *ret = realloc(ptr, size);
	if (ptr == NULL)
	{
		fprintf(stderr, "error: realloc() failed to allocate memory of size %" PRIu64"\n", size);
		exit(EXIT_FAILURE);
	}
	return ret;
}
