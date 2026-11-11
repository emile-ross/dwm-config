#include "header.h"

#include <inttypes.h>
#include <stdlib.h>

#define BASE_ARGS (3)

#define ARG_CHECK(FLAG_STRING) \
	if (argc <= i) \
	{ \
		fprintf(stderr, "the %s flag expected an argument\n", FLAG_STRING); \
		return ret_args; \
	}

/* this crashes the program whenever we encounter an error
 * these errors are not critical and parsing can still continue 
 * however the program will behave in an unpredictable 
 * way if it encounters some errors since some features get disabled */
static bool crash_on_failure = false;	/* default is false */

struct arguments parse_args(const uint32_t argc, char *argv[])
{
	struct arguments ret_args =
	{ 
		{ NULL },
		NULL,
		0,
		false
	};

	/* allocate the flags on the heap */
	size_t increment = 1;
	size_t num_elements = BASE_ARGS;
	ret_args.flags = smalloc(sizeof(flag_types) * num_elements);

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
				return ret_args;
			}
			ret_args.flags = ptr;
		}
		printf("Element #%"PRIu32" \n", i);
		if (scmp("-p", argv[i]) || scmp("--path", argv[i]) || scmp(argv[i], "--file-path"))
		{
			printf("Flag: %s was found\n", argv[i]);	/* debug print */
			i++;
			ARG_CHECK(argv[i - 1]);
			ret_args.source.file_path = argv[i];
		}
		else if (scmp("-p", argv[i]) || scmp("--prev", argv[i]))
		{
			printf("%s was found\n", argv[i]);
			ret_args.flags[current_index] = PREV_EVENT;
			current_index++;
		}
		else if (scmp("-s", argv[i]) || scmp("--silent", argv[i]))
		{
			ret_args.silent = true;
		}
		else if (scmp("-n", argv[i]) || scmp("--next", argv[i]))
		{
			printf("%s was found\n", argv[i]);
			ret_args.flags[current_index] = NEXT_EVENT;
			current_index++;
		}
		else if (scmp("-H", "--help"))
		{
			ret_args.flags[current_index] = HELP;
			current_index++;
		}
		else
		{
			if (current_index == 0)
			{
				current_index++;
				continue;
			}

			if (ret_args.source.file_path == NULL)
			{
				ret_args.source.file_path = argv[i];
			}
			else
			{
				ret_args.flags[current_index] = INVALID_FLAG;
				current_index++;
			}
		}
	}

	if (ret_args.source.file_path == NULL)
	{
		fprintf(stderr, "\x1B[1m\x1b[33mWarning\x1b[0m\x1b[33m: no filename specified \x1b[0m\n");
	}

	return ret_args;
}
