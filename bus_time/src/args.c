#include "header.h"

void parse_args(const uint32_t argc, const char *restrict argv[])
{
	for (uint32_t i = 0; i < argc; i++)
	{
		if (scmp("-c", argv[i]))
		{
			printf("-c was found\n");
		}
	}
}
