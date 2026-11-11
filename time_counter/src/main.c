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
		argument_data = parse_args((uint32_t)argc, argv);
	}


	file_data time_array = fread_times(argument_data.source.file_path, !(argument_data.silent));

	bool check_next_day = false;

	time_type next = get_next_time(time_array.time, &check_next_day, time_array.number_of_times);
	char *str = time_to_text(next);
	if (!argument_data.silent)
	{
		printf("For bus %s\n", time_array.title);
		printf("next bus time: %s\n", str);
	}
	else
	{
		printf("%s\n", str);
	}
	free(str);

	free(time_array.time);
	free(time_array.title);
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
