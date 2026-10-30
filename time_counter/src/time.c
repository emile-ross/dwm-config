#include "header.h"

#include <ctype.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

#define TIME_TO_MINS(TIME_ARG) \
	(int16_t)((TIME_ARG.hour * 60) + TIME_ARG.minute)

time_type get_next_time(time_type *time_array, bool *check_next_day, uint32_t num_times)
{
	time_type return_value = { 0, 0 };

	if (time_array == NULL)
	{
		fprintf(stderr, "error: passing NULL pointer to get_next_time() function\n");
		return return_value;
	}

	time_t t = time(NULL);
	struct tm *current_time = localtime(&t);
	time_type cur = 
	{
		(int8_t)current_time->tm_hour,
		(int8_t)current_time->tm_min
	};

	int16_t current_seconds = TIME_TO_MINS(cur);
	int16_t return_minutes = -1;

	uint32_t i = 0;
	if (!(*check_next_day))
	{
		for (i = 0; i < num_times; i++)
		{
			if (current_seconds > TIME_TO_MINS(time_array[i]))
				continue;

			if (return_minutes != -1)
			{
				if (return_minutes < TIME_TO_MINS(time_array[i]))
				{
					continue;
				}
			}
			return_minutes = TIME_TO_MINS(time_array[i]);
			return_value = time_array[i];
			(*check_next_day) = false;
		}
	}
	else
	{
		for (i = 0; i < num_times; i++)
		{
			if (return_minutes != -1)
			{
				if (return_minutes < TIME_TO_MINS(time_array[i]))
				{
					continue;
				}
			}
			return_minutes = TIME_TO_MINS(time_array[i]);
			return_value = time_array[i];
			(*check_next_day) = false;
		}
	}
	/* (*current_time) localtime() is garbage collected 
	 * and it doesn't need to be freed */
	return return_value;
}
int16_t time_to_mins(time_type time_arg)
{
	/* converts time hours to minutes */
	int16_t mins = (time_arg.hour * 60);
	mins += time_arg.minute;

	return mins;
}
