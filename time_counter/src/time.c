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

	if (time_array == NULL)
	{
		fprintf(stderr, "error: passing NULL pointer to get_next_time() function\n");
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
	bool check_next_day = true;
	uint16_t current_attempt = 0;

	uint32_t i = 0;
	/* (*current_time) localtime() is garbage collected 
	 * and it doesn't need to be freed */
	return return_value;
}
