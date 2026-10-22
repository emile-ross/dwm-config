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
	time_type **time;
} file_data;

enum date_str_state
{
	EXPECT_SEPARATOR = 0,
	EXPECT_ERROR = 1,
	EXPECT_HOUR = 2,
	EXPECT_MINUTE = 3
};

#endif /* DATA_TYPES_H */
