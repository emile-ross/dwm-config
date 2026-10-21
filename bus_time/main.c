#include "header.h"

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

int main(const int argc, const char *restrict argv[])
{
	if (argc > 1)
	{
		if (argc > 3)
		{
			printf("No need for this many arguments\n");
			help_message();
		}
		parse_args((uint32_t)argc, argv);
		return 0;
	}

	/* this will eventually read from a file 
	 * and then print something in a json format
	 * in order for it to be compatible with waybar */
	printf("%lu\n", time(NULL));
	return 0;
}


void help_message(void)
{
	printf(
			"-c --configure\n"
			"-h --help\n"
			"-n --next-bus\n");
}
