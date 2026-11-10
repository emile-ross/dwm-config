#include "header.h"

#include <ctype.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

#define TIME_TO_MINS(TIME_ARG) \
	(int16_t)((TIME_ARG.hour * 60) + TIME_ARG.minute)

time_type get_next_time(const time_type *restrict time_array, bool *check_next_day, uint32_t num_times)
{
	time_type return_value = { 0, 0 };

	if (time_array == NULL || check_next_day == NULL || num_times == 0)
	{
		fprintf(stderr, "error: invalid arguments to get_next_time() function\n");
		return return_value;
	}

	time_t t = time(NULL);
	struct tm *current_time = localtime(&t);

	if (current_time == NULL)
	{
		fprintf(stderr, "error: unable to retrieve current time\n");
		return return_value;
	}

	int16_t current_minutes = (int16_t)((current_time->tm_hour * 60) + current_time->tm_min) ;
	int16_t next_minutes = 0;
	bool not_found = true;
	uint16_t current_attempt = 0;

	for (uint32_t i = 0; i < num_times; i++)
	{
		current_attempt = TIME_TO_MINS(time_array[i]);

		if (current_attempt < 0 || current_attempt >= 24 * 60)
			continue;

		if (!(*check_next_day) && (current_attempt < current_minutes))
			continue;

		if (not_found || current_attempt < next_minutes)
		{
			next_minutes = current_attempt;
			not_found = false;
			return_value = time_array[i];
		}
	}
	/* (*current_time) localtime() is garbage collected 
	 * and it doesn't need to be freed */
	return return_value;
}
