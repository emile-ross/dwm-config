#include "header.h"

#include <ctype.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

time_type extract_time(bool *valid_time, char *line_buf, size_t length)
{
	enum date_str_state state = EXPECT_HOUR;
	enum date_str_state prev_state = EXPECT_HOUR;
	time_type ret = { 0 , 0 };
	bool done = false;

	for (uint16_t i = 0; !done && i < length; i++)
	{
		char cur = line_buf[i];
		switch (state)
		{
		case EXPECT_HOUR:
		{
			if (!(isdigit(cur)))
			{
				break;
			}

			uint16_t j = i;
			char str[4] = { 0 };
			uint8_t index = 0;
			for (; sizeof(str) > index && isdigit(line_buf[j]); j++)
			{
				str[index] = line_buf[j];
				index++;
			}

			char *endptr = NULL;
			long input = strtol(str, &endptr, 10);
			if (input > 60)
			{
				fprintf(stderr, "out of bounds value %" PRId64 "\nline: \"%s\"\n", input, line_buf);
				*valid_time = false;
				return ret;
			}
			ret.hour = (int8_t)input;

			prev_state = EXPECT_HOUR;
			state = EXPECT_SEPARATION;
			break;
		}
		case EXPECT_SEPARATION:
			/* if none of these match we continue checking for characters */
			if (!( (cur == ':') || (cur == ',') || (cur == ' ')))
			{
				if (prev_state == EXPECT_MINUTE)
				{
					if (!( (cur == 'm') || (cur == 'M') ))
						break;
				}
				else if (prev_state == EXPECT_HOUR)
				{
					if (!( (cur == 'h') || (cur == 'H') ))
						break;
					else
						state = EXPECT_MINUTE;
				}
			}
			/* we're still executing if one of the characters above matched */
			state = prev_state + 1;
			/* EXPECT_SEPARATION should never be incremented 
			 * if it gets incremented it triggers an error */
			prev_state = EXPECT_SEPARATION;

			break;
		case EXPECT_MINUTE:
		{
			if (!(isdigit(cur)))
			{
				break;
			}

			uint16_t j = i;
			char str[4] = { 0 };
			uint8_t index = 0;
			for (; sizeof(str) > index && isdigit(line_buf[j]); j++)
			{
				str[index] = line_buf[j];
				index++;
			}

			char *endptr = NULL;
			long input = strtol(str, &endptr, 10);
			if (input > 60)
			{
				fprintf(stderr, "out of bounds value %ld\nline: \"%s\"\n", input, line_buf);
				*valid_time = false;
				return ret;
			}

			/* because minute is the highest precision 
			 * this needs to be edited if it's changed to seconds */
			ret.minute = (int8_t)input;
			done = true;
			*valid_time = true;
			break;
		}
		case EXPECT_ERROR:
			fprintf(stderr, "Internal error, prev_state was set to EXPECT_SEPARATION and it was incremented and switched onto\n");
			printf("line being parsed: \"%s\" at index %u\n", line_buf, i);
			*valid_time = false;
			return ret;
		default:
			fprintf(stderr, "I truly have no idea what's going on in here\n");
			*valid_time = false;
			return ret;
		}
	}

	return ret;
	
}


time_type get_next_time(time_type *time_array, bool *check_next_day, uint32_t num_times)
{
	time_type return_value = { 0, 0 };
	bool valid_time = false;

	if (time_array == NULL)
	{
		fprintf(stderr, "error: passing NULL pointer to get_next_time() function\n");
		return return_value;
	}

	time_t t = time(NULL);
	struct tm *current_time = localtime(&t);
	time_type cur = 
	{
		current_time->tm_hour,
		current_time->tm_min,
	}

	int16_t current_seconds = cur;
	int16_t return_minutes = -1;

	uint32_t i = 0;
	if (!(check_next_day))
	{
		for (i = 0; i < num_times; i++)
		{
			if (current_seconds > time_array[i])
				continue;

			if (return_minutes != -1)
			{
				if (return_minutes < time_array[i])
				{
					continue;
				}
			}
			return_minutes = time_to_mins(time_array[i]);
			return_value = time_array[i];
			valid_time = true;
		}
	}
	else
	{
		for (i = 0; i < num_times; i++)
		{
			if (time_array[i].hour < (int8_t)current_time->tm_hour)
				continue;
			if (time_array[i].minute < (int8_t)current_time->tm_min)
				continue;

			if (time_array[i].hour > return_value.hour)
				continue;
			if (time_array[i].minute > return_value.minute)
				continue;

			return_value.hour = (int8_t)current_time->tm_hour;
			return_value.minute = (int8_t)current_time->tm_min;
			valid_time = true;
		}
	}
	/* *current_time localtime() is garbage collected 
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
