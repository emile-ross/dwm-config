#include "header.h"

void *smalloc(size_t size)
{
	void *ptr = malloc(size);
	if (ptr == NULL)
	{
		fprintf(stderr, "");
		exit(EXIT_FAILURE);
	}
	return ptr;
}
