#include "header.h"

#include <inttypes.h>
#include <stdbool.h>

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


	fread_times("example.txt");
	bool success = false;
	bool check_next_day = false;
	do {
	} while (check_next_day);

	time_type a = extract_time(&success, "12:04", 5);
	time_type b = extract_time(&success, "13:30", 5);
	time_type c = extract_time(&success, "14:25", 5);
	time_type d = extract_time(&success, "20:59", 5);

	time_type arr[4] = { a, b, c, d };

	/* this will eventually read from a file 
	 * and then print something in a json format
	 * in order for it to be compatible with waybar */
	/* set extracted to the current time of day 
	 * but then set hour & minute to the one we got in the file */



	return 0;
}


void help_message(void)
{
	printf(
			"-c --configure\n"
			"-h --help\n"
			"-n --next-bus\n");
}
