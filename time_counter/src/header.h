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
	time_type get_next_time(const time_type *restrict time_array, bool *check_next_day, uint32_t num_times, char **tooltip);

/* memory_safety.c */
	void *smalloc(size_t size);
	void *srealloc(void *ptr, size_t size);

/* menu.c */
	void display_menu(void);
	int64_t get_input(bool *success, int16_t lb, int16_t ub);


/* strings.c */
	char *time_to_text(time_type time);

/* printing.c */
	void json_printing(time_type date, const char *restrict tag, bool pretty, char *tooltip);
	char *create_tooltip(int8_t hour, int8_t min);

#endif /* HEADER_H */
