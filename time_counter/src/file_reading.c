#include "header.h"

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define MAX_LINE_LEN (256)
#define MAX_NUM_TIMES (256)

#define BASE_ELEMENTS (8)
#define ELEMETS_INRC (4)

#define SET_TITLE_BUF(buffer_length) \
	ret.title = smalloc(buffer_length); \
	strncpy(ret.title, line, buffer_length); \
	ret.title[buffer_length - 2] = '\0';
	

file_data fread_times(const char *restrict file_path, bool verbose)
{
	FILE *fp = fopen(file_path, "r");
	file_data ret = { NULL, NULL, 0 };
	time_type *times_array = NULL;
	uint16_t num_elements_alloc = BASE_ELEMENTS;

	if (fp == NULL)
	{
		fprintf(stderr, "No such file or directory \"%s\"\n", file_path);
		return ret;
	}

	times_array = smalloc(sizeof(time_type) * num_elements_alloc);

	char line[MAX_LINE_LEN] = { 0 };

	/* declared as 16 bit even though max is 256 times
	 * just in case we increase it to something else */
	uint16_t line_number = 0;
	
	/* there is no actual limit to the maximum number of times that can be in a file,
	 * we could remove this condition entirely but it's still preferable if we don't
	 * because it will prevent parsing through an enormous file with tons of invalid
	 * data.  current_entry is used as an iterator through the times_array[] on heap
	 */
	uint16_t current_entry = 0;
	while (fgets(line, MAX_LINE_LEN - 1, fp) && MAX_NUM_TIMES > current_entry)
	{
		if (verbose)
			printf("line: %s", line);
		line_number++;
		size_t line_len = strlen(line);
		if (line_len < 4)
		{
			if (line_number == 1)
			{
				SET_TITLE_BUF(line_len + 1);
				continue;
			}
				
			fprintf(stderr, "Line %" PRId16 " is missing parameters\n",
					line_number);
			continue;
		}
		bool valid_time = false;
		time_type returned_time = extract_time(&valid_time, line, line_len);
		if (valid_time)
		{
			times_array[current_entry] = returned_time;
			current_entry++;

			if (verbose)
			{
				char *time = time_to_text(returned_time);
				printf("Valid time: '%s'\n", time);
				free(time);
			}
		}
		else 
		{
			const char *tag = "TAG";
			bool is_tag = true;
			size_t tag_len = strlen(tag);
			for (uint8_t i = 0; i < strlen(tag); i++)
			{
				if (!(line[i] == tag[i]))
				{
					is_tag = false;
					break;
				}
			}

			if (is_tag)
			{
				/* TODO store tag in argument struct */
				size_t index = strcspn(line, ":=>-<");
				char *tag_str = strdup(line + index + 1);
				/* TODO use smalloc() with snprintf() not strdup() */
				if (tag_str == NULL)
				{
					fprintf(stderr, "strdup() call failed to allocate memory for tag string\n");
					return ret;
				}
				
				printf("Tag: \'%s\'\n", tag_str);
			}
			else if (ret.title == NULL)
			{
				SET_TITLE_BUF(line_len + 1);
			}
			else
			{
				line[line_len - 1] = '\0';
				fprintf(stderr, "\x1b[31mUnknown string: \"%s\"\n\x1B[0m", line);
			}
		}
	}

	/* assign the pointer to the array to the return value this pointer
	 * will then be used in order to go through all times possible */
	ret.time = times_array;
	ret.number_of_times = current_entry;

	if (verbose)
	{
		printf("Title: %s\n", ret.title);
	}

	return ret;
}

