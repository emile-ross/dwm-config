#include "header.h"

bool scmp(const char *restrict arg, const char *restrict str)
{
	/* match the argument to the string */
	uint16_t i = 0;	/* supports up to 65535 characters */

	while (arg[i] != '\0' && str[i] != '\0')
	{
		if (arg[i] != str[i])
			return false;
		i++;
	}
	return true;
}

/* With size version */
bool str_n_compare(const char *restrict arg, const char *restrict str, size_t size)
{
	size_t i = 0;

	while (i < size)
	{
		if (arg[i] != str[i])
			return false;

		if (arg[i] == '\0')
			return true;

		i++;
	}
	return true;
}

