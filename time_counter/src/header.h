#ifndef HEADER_H
#define HEADER_H
/* prevent double include */

#include "data_types.h"
#include "config.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* cmp.c */
	bool scmp(const char *restrict arg, const char *restrict str);
	bool str_n_compare(const char *restrict arg, const char *restrict str, size_t size);

/* args.c */
	struct arguments parse_args(const uint32_t argc, char *argv[]);
	void help_message(void);

/* file_reading.c */
	file_data fread_times(const char *restrict file_path, bool verbose);

/* time.c */
	time_type extract_time(bool *valid_time, char *line, size_t length);
	time_type get_next_time(const time_type *restrict time_array, bool *check_next_day, uint32_t num_times);

/* memory_safety.c */
	void *smalloc(size_t size);
	void *srealloc(void *ptr, size_t size);


/* strings.c */
char *time_to_text(time_type time);

void json_printing(time_type date, const char *restrict title, const char *restrict tag, bool pretty);

#endif /* HEADER_H */
