#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


void display_menu(void)
{
	int16_t num_options = 2;
	uint16_t input = 0;
	bool success = true;
	while (1)
	{
		input = (uint16_t)get_input(0, num_options, &success);
		if (input == 0)
		{
			break;
		}
		else if (input == 1)
		{

		}
	}
	return;
}

int64_t get_input(int16_t lb, int16_t ub)
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
		fprintf(stderr, "input is larger than upper bound\n");
		/* success = false; */
	}
	else if (input < lb)
	{
		fprintf(stderr, "input is lower than lower bound\n");
		/* success = false; */
	}

	/* this might need a cast on systems
	 * where a long isn't 64 bit wide */
	return input;
}
