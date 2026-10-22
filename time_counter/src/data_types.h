#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdint.h>


typedef struct
{
	int8_t hour;
	int8_t minute;
} time_type;

typedef struct
{
	char *title;
	time_type *time;
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
	CONFIGURE,
	HELP,
	NEXT_EVENT,
	PREV_EVENT
} flag_types;

struct arg_types 
{
	union {
		char *file_path;
		char *time_string;
	} source;
};

#endif /* DATA_TYPES_H */
