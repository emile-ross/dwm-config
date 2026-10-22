#include "header.h"

#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN (256)
#define MAX_NUM_TIMES (256)

#define BASE_ELEMENTS (8)
#define ELEMETS_INRC (4)

file_data fread_times(char *file_path)
{
	FILE *fp = fopen(file_path, "r");
	file_data ret = { NULL, NULL };
	time_type **times_array = NULL;
	uint16_t num_elements_alloc = BASE_ELEMENTS;

	if (fp == NULL)
	{
		fprintf(stderr, "No such file or directory \"%s\"\n", file_path);
		return ret;
	}

	times_array = malloc(sizeof(time_type) * num_elements_alloc);
	if (times_array == NULL)
	{
		fprintf(stderr, "error: malloc() failed to allocate memory of size %lu\n", sizeof(time_type) * num_elements_alloc);
		fclose(fp);
		return ret;
	}


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
		line_number++;
		size_t line_len = strlen(line);
		if (line_len < 4)
		{
			fprintf(stderr, "Line %d is missing parameters\n", line_number);
			continue;
		}
		bool valid_time = true;
		time_type returned_time = extract_time(&valid_time, line, line_len);
		if (valid_time)
		{
			(*times_array)[current_entry] = returned_time;
			current_entry++;
		}
	}

	/* assign the pointer to the array to the return value this pointer
	 * will then be used in order to go through all times possible */
	ret.time = times_array;

	fclose(fp);
	return ret;
}

