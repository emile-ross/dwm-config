#include "header.h"

bool scmp(const char *arg, const char *str)
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
