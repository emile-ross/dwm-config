#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdint.h>

typedef struct
{
	char *title;
	time_type **time;
} file_data;

typedef struct
{
	int8_t hour;
	int8_t minute;
} time_type;

enum date_str_state
{
	EXPECT_HOUR,
	EXPECT_SEPARATOR,
	EXPECT_MINUTE
};

#endif /* DATA_TYPES_H */
