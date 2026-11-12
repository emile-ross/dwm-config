#include "header.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

int main(const int argc, char **argv)
{
	struct arguments argument_data = { { NULL }, NULL, 0, false, false };

	if (argc > 1)
	{
		if (argc > 3)
		{
			printf("No need for this many arguments\n");
			help_message();
		}
		argument_data = parse_args((uint32_t)argc, argv);
	}

	bool default_path_used = false;
	if (argument_data.source.file_path == NULL)
	{
		default_path_used = true;
		char *home_path = getenv("HOME");
		size_t length = 1 + (unsigned)snprintf(NULL, 0, default_config_path, home_path);
		char *fp = smalloc(length);
		snprintf(fp, length, default_config_path, home_path);
		argument_data.source.file_path = fp;
		/* fp must be freed */
	}

	file_data time_array = fread_times(argument_data.source.file_path, !(argument_data.silent));
	if (default_path_used)
	{
		free(argument_data.source.file_path);
	}

	bool check_next_day = false;

	time_type next = get_next_time(time_array.time, &check_next_day, time_array.number_of_times);
	if (!argument_data.silent)
	{
		char *str = time_to_text(next);
		printf("For bus %s\n", time_array.title);
		printf("next bus time: %s\n", str);
		free(str);
	}
	else
	{
		json_printing(next, time_array.title, time_array.tag, argument_data.pretty);
	}

	free(time_array.time);
	free(time_array.title);
	free(argument_data.flags);
	free(time_array.tag);

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
