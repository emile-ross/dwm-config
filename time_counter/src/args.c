#include "header.h"

struct arg_types parse_args(const uint32_t argc, const char *restrict argv[])
{
	struct arg_types ret_args =
	{ 
		NULL
	};
	for (uint32_t i = 0; i < argc; i++)
	{
		if (scmp("-s", argv[i]))
		{
			printf("-s was found\n");
		}
	}
	return ret_args;
}
