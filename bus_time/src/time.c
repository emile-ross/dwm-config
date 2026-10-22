#include "header.h"

#define MAX_LINE_LEN (256)
#define MAX_NUM_LINES (256)

time_type *get_next_time(char *file_path)
{
	FILE *fp = fopen(file_path);

	if (fp == NULL)
	{
		fprintf(stderr, "No such file or directory \"%s\"\n", file_path);
		return NULL;
	}

	char line[]
	while (fgets(line, MAX_LINE_LEN - 1, fp))
	{

	}

	fclose(fp);
	return NULL;
}
