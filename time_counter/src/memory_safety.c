#include "header.h"

#include <stdlib.h>

void *smalloc(size_t size)
{
	void *ptr = malloc(size);
	if (ptr == NULL)
	{
		fprintf(stderr, "error: malloc() failed to allocate memory of size %" PTRIu64"\n", );
		exit(EXIT_FAILURE);
	}
	return ptr;
}
