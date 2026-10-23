#include "header.h"

#include <inttypes.h>
#include <stdlib.h>

#define BASE_ARGS (3)

/* this crashes the program whenever we encounter an error
 * these errors are not critical and parsing can still continue 
 * however the program will behave in an unpredictable 
 * way if it encounters some errors since some features get disabled */
static bool crash_on_failure = false;	/* default is false */

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



	size_t current_index = 0;
	for (uint32_t i = 0; i < argc; i++)
	{
		if (current_index + 1 >= num_elements)
		{
			num_elements += increment;
			increment <<= 1;
			flag_types *ptr = realloc(ret_args.flags, sizeof(flag_types) * num_elements);
			if (ptr == NULL)
			{
				fprintf(stderr, "error: malloc() failed to allocate memory "
						"of size %" PRIu64 " bytes\n", sizeof(flag_types) * num_elements);
				if (crash_on_failure)
				{
					fprintf(stderr, "The program could've recovered but crash_on_failure"
							" was set to true, therefore we exited the program\n");
					free(ret_args.flags);
					exit(EXIT_FAILURE);
				}
				fprintf(stderr, "all flags following index %" PRIu32" will be ignored\n"
						"%" PRIu32 " out of %"PRIu32" arguments were parsed\n", 
						i, i + 1, argc);
			}
			ret_args.flags = ptr;
		}
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
