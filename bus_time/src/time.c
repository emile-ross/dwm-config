#include "header.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN (256)
#define MAX_NUM_TIMES (256)

#define BASE_ELEMENTS (8)
#define ELEMETS_INRC (4)

file_data get_next_time(char *file_path)
{
	FILE *fp = fopen(file_path, "r");

	file_data ret = { NULL, NULL };
	time_type **times_array = malloc(sizeof(time_type) * BASE_ELEMENTS);
	if (times_array == NULL)
	{
		fprintf(stderr, "error: malloc() failed to allocate memory of size %lu\n", sizeof(time_type) * num_elements_alloc);
		return ret;
	}


	if (fp == NULL)
	{
		fprintf(stderr, "No such file or directory \"%s\"\n", file_path);
		return ret;
	}

	char line[MAX_LINE_LEN] = { 0 };

	* declared as 16 bit even though max is 256 times
	 * just in case we increase it to something else *
	uint16_t line_number = 0;
	
	while (fgets(line, MAX_LINE_LEN - 1, fp))
	{
		line_number++;
		size_t line_len = strlen(line);
		if (line_len < 4)
		{
			fprintf(stderr, "Line %d is missing parameters\n", line_number);
			continue;
		}
	}

	fclose(fp);
	return ret;
}

time_type extract_time(bool *valid_time, char *line, size_t length)
{
	enum date_str_state state = EXPECT_HOUR;
	enum date_str_state prev_state = EXPECT_HOUR;
	time_type ret = { 0 , 0 };
	bool done = false;

	for (uint16_t i = 0; !done && i < length; i++)
	{
		char cur = line[i];
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
			for (; sizeof(str) > index && isdigit(line[j]); j++)
			{
				str[index] = line[j];
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
			for (; sizeof(str) > index && isdigit(line[j]); j++)
			{
				str[index] = line[j];
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
