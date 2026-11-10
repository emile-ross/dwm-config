#include "header.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

int main(const int argc, char **argv)
{
	struct arguments argument_data;
	if (argc > 1)
	{
		if (argc > 3)
		{
			printf("No need for this many arguments\n");
			help_message();
		}
		argument_data= parse_args((uint32_t)argc, argv);

	}

	file_data time_array = fread_times(argv[1]);

	free(time_array.time);

	/* for now this is useless 
	bool success = false;
	bool check_next_day = false;
	do {
	} while (check_next_day);
	*/

	/* this will eventually read from a file 
	 * and then print something in a json format
	 * in order for it to be compatible with waybar */
	/* set extracted to the current time of day 
	 * but then set hour & minute to the one we got in the file */


	free(argument_data.flags);
	return 0;
}


void help_message(void)
{
	printf(
			"-c --configure\n"
			"-h --help\n"
			"-p --path, --file-path\n"
			"-n --next-bus\n");
}
