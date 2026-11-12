#include "header.h"

#include <ctype.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

#define TIME_TO_MINS(TIME_ARG) \
	(int16_t)(TIME_ARG.hour * 60 + TIME_ARG.minute)

time_type get_next_time(const time_type *restrict time_array, bool *check_next_day, uint32_t num_times, char **tooltip)
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
	int16_t current_attempt = 0;

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

	if (not_found)
	{
		/* if next_day is true
		 * wrap around to the earliest occurrence tomorrow */
		for (uint32_t i = 0; i < num_times; i++)
		{
			current_attempt = TIME_TO_MINS(time_array[i]);

			if (current_attempt < 0 || current_attempt >= 24 * 60)
				continue;

			if (not_found || current_attempt < next_minutes)
			{
				next_minutes = current_attempt;
				not_found = false;
				return_value = time_array[i];
			}
		}

		*check_next_day = true;
	}
	else
	{
		*check_next_day = false;
	}

	printf("hours %d\nMinutes %d\n", next_minutes / 60, next_minutes % 60);
	printf("hours %d\nMinutes %d\n", current_minutes / 60, current_minutes % 60);

	int16_t diff = next_minutes - current_minutes;
	char *buffer = NULL;
	if (diff > 0)
	{
		char *template = "in %dh, %dm";
		int8_t hour = (int8_t)diff / 60;
		int8_t min = (int8_t)diff % 60;
		size_t size = 1 + (unsigned)snprintf(NULL, 0, template, hour, min);

		buffer = smalloc(size);
		snprintf(buffer, size, template, hour, min);
		printf("%s\n", buffer);
		free(buffer);
	}
	printf("%s\n", create_tooltip((int8_t)(diff / 60), (int8_t)(diff % 60)));

	/* (*current_time) localtime() is garbage collected 
	 * and it doesn't need to be freed */
	return return_value;
}

char *create_tooltip(int8_t hour, int8_t min)
{
	char *buffer = NULL;
	char *template = "event in %dh, %dm";
	size_t size = 1 + (unsigned)snprintf(NULL, 0, template, hour, min);

	buffer = smalloc(size);
	snprintf(buffer, size, template, hour, min);

	return buffer;
}
