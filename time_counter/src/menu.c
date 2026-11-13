#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define GET() \
	


void display_menu(void)
{
	uint16_t num_options = 2;
	uint16_t input = 0
	while (1)
	{
		input = GET();

		if (input == 0)
		{
			break;
		}
	}
	return;
}

uint16_t get_input(uint16_t lb, uint16_t ub)
{
	size_t size_input = 16;
	char *input_buffer = smalloc(size_input);

	if (fgets(input_buffer, (int32_t)size_input, stdin))
	{
		printf("%s\n", input_buffer);
	}
	else
	{
		fprintf(stderr, "fgets() failed to get input\n");
		exit(EXIT_FAILURE);
	}

	char *endptr = NULL;
	long input = strtol(input_buffer, &endptr, 10);

	if (input > ub)
	{
	}
	else if (input < lb)
	{
	}

	return 0;
}
