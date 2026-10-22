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


	bool success = false;
	time_type a = extract_time(&success, "12:04", 5);

	/* this will eventually read from a file 
	 * and then print something in a json format
	 * in order for it to be compatible with waybar */
	int64_t current_time = time(NULL);
	/* set extracted to the current time of day 
	 * but then set hour & minute to the one we got in the file */
	struct tm extracted = *localtime(&current_time);
	extracted.tm_hour = a.hour;
	extracted.tm_min = a.minute;
	extracted.tm_sec = 0;

	/* check if time is coming later this day */ 
	if (mktime(&extracted) > current_time)
	{
		printf("Time is upcoming\n");
	}

	printf("%ld\n", current_time);
	printf("%ld\n", (current_time) % (24 * 60));

	return 0;
}


void help_message(void)
{
	printf(
			"-c --configure\n"
			"-h --help\n"
			"-n --next-bus\n");
}
