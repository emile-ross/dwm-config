#include "header.h"

#include <ctype.h>

#define MAX_LINE_LEN (256)
#define MAX_NUM_TIMES (256)

void get_next_time(char *file_path)
{
	FILE *fp = fopen(file_path);

	if (fp == NULL)
	{
		fprintf(stderr, "No such file or directory \"%s\"\n", file_path);
		return NULL;
	}

	char line[MAX_LINE_LEN] = { 0 };

	/* declared as 16 bit even though max is 256 times
	 * just in case we increase it to something else */
	uint16_t line_number = 0;
	
	while (fgets(line, MAX_LINE_LEN - 1, fp))
	{
		size_t line_len = strlen(line);
		if (line_len < 5)
		{
			fprintf(stderr, "Line %d is missing parameters\n");
		}
	}

	fclose(fp);
	return NULL;
}

time_type extract_time(bool *valid_time, char *line, size_t length)
{
	enum date_str_state state = EXPECT_HOUR;
	time_type ret = { 0 , 0 };

	for (uint16_t i = 0; i < length; i++)
	{
		switch (state)
		{
		case EXPECT_HOUR:
			break;
		case EXPECT_SEPARATION:
			break;
		case EXPECT_MINUTE:
			break;
		}
	}
	
}
