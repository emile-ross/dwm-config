#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		if (argc > 3)
		{
			printf("No need for this many arguments\n");
			help_message();
		}
		parse_args(argc, argv);
		return 0;
	}

	/* this will eventually read from a file 
	 * and then print something in a json format
	 * in order for it to be compatible with waybar */
	printf("%u\n", time(NULL));
	return 0;
}

