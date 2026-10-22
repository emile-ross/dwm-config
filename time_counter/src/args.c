#include "header.h"

struct arg_types parse_args(const uint32_t argc, const char *restrict argv[])
{
	struct arg_types ret_args =
	{ 
		{ NULL },
		NULL
	};
	for (uint32_t i = 0; i < argc; i++)
	{
		if (scmp("-p", argv[i]) || scmp("--path", argv[i]))
		{
			/* TODO write something to the heap allocated
			 * array of command line arguments */
			printf("-p was found\n");
		}
		else if (scmp("-s", argv[i]) || scmp("--string", argv[i]))
		{
			/* TODO write something to the heap allocated
			 * array of command line arguments */
			printf("--string was found\n");
		}
	}
	return ret_args;
}
