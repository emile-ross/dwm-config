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
	void parse_args(const uint32_t argc, const char *restrict argv[]);
	void help_message(void);

#endif /* HEADER_H */
