#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	int8_t hour;
	int8_t minute;
} time_type;

typedef struct
{
	char *title;
	time_type *time;
	char *tag;
	uint16_t number_of_times;
} file_data;

enum date_str_state
{
	EXPECT_SEPARATION = 0,
	EXPECT_ERROR = 1,
	EXPECT_HOUR = 2,
	EXPECT_MINUTE = 3
};

typedef enum
{
	INVALID_FLAG,
	HELP,
	NEXT_EVENT,
	PREV_EVENT
} flag_types;

struct arguments 
{
	union {
		char *file_path;
		const char *restrict time_string;
	} source;
	flag_types *flags;	/* heap allocated array */
	uint16_t num_flags;
	bool silent;
};

#endif /* DATA_TYPES_H */
