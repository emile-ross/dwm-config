#ifndef HEADER_H
#define HEADER_H
/* prevent double include */

#include "data_types.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


/* cmp.c */
	bool scmp(const char *restrict arg, const char *restrict str);

/* args.c */
	struct arguments parse_args(const uint32_t argc, const char *restrict argv[]);
	void help_message(void);
	time_type extract_time(bool *valid_time, char *line, size_t length);

/* file_reading.c */
	file_data fread_times(char *file_path);
#endif /* HEADER_H */
