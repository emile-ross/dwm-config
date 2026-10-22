#include "header.h"

#include <inttypes.h>
#include <stdlib.h>

#define BASE_ARGS (3)

struct arguments parse_args(const uint32_t argc, const char *restrict argv[])
{
	struct arguments ret_args =
	{ 
		{ NULL },
		NULL
	};

	/* allocate the flags on the heap */
	size_t increment = 1;
	size_t num_elements = BASE_ARGS;
	ret_args.flags = malloc(sizeof(flag_types) * num_elements);

	if (ret_args.flags == NULL)
	{
		fprintf(stderr, "error: in parse_args, malloc() failed to allocate memory"
				"of size %" PRId64 "\n", sizeof(flag_types) * num_elements);
		exit(EXIT_FAILURE);
	}

	/*
	CONFIGURE,
	HELP,
	NEXT_EVENT,
	PREV_EVENT
	*/



	for (uint32_t i = 0; i < argc; i++)
	{
		printf("Element #%"PRIu32" \n", i);
		if (scmp("-p", argv[i]) || scmp("--path", argv[i]))
		{
			/* TODO write something to the heap allocated
			 * array of command line arguments */
			printf("-p was found\n");
		}
		else if (scmp("-p", argv[i]) || scmp("--prev", argv[i]))
		{
			printf("--string was found\n");
		}
		else if (scmp("-n", argv[i]) || scmp("--next", argv[i]))
		{
			printf("--string was found\n");
		}
		else if (scmp("-s", argv[i]) || scmp("--string", argv[i]))
		{
			/* TODO write something to the heap allocated
			 * array of command line arguments */
			printf("--string was found\n");
		}
		else
		{
			INVALID_FLAG;
		}

	}
	return ret_args;
}
