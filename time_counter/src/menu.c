#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void print_menu(void);

void display_menu(void)
{
	int16_t num_options = 2;
	uint16_t input = 0;
	bool success = true;
	while (1)
	{
		print_menu();
		input = (uint16_t)get_input(&success, 0, num_options);
		if (input == 0)
		{
			break;
		}
		else if (input == 1)
		{
		}
		else if (input == 2)
		{
		}
	}
	return;
}

int64_t get_input(bool *success, int16_t lb, int16_t ub)
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

	/* equivalent to *endptr */
	if (endptr[0] != '\n')
	{
		*success = false;
	}

	if (input > ub)
	{
		fprintf(stderr, "input is larger than upper bound\n");
		*success = false;
	}
	else if (input < lb)
	{
		fprintf(stderr, "input is lower than lower bound\n");
		*success = false;
	}
	else
	{
		/* this might need a cast on systems
		 * where a long isn't 64 bit wide */
		*success = true;
		return input;
	}

	return -1;
}

void print_menu(void)
{
	printf(
			"[1] New \"events.txt\" file\n"
			"[2] Validate a file\n"
			"[0] Quit this program\n"
			);
}

