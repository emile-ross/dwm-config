#include "header.h"

#include "stdlib.h"

void json_printing(time_type date, const char *restrict title, const char *restrict tag, bool pretty)
{
	const char *restrict json_format;
	if (pretty)
		json_format = "{\n\t\"text\": \"%s %s\",\n\t\"tooltip\": \"%s\",\n\t\"class\": \"next-event\"\n} ";
	else
		json_format = "{ \"text\": \"%s %s\", \"tooltip\": \"%s\", \"class\": \"next-event\" } ";

	char *formatted_output = NULL;
	char *date_str = time_to_text(date);

	/* get size & allocate memor y*/
	size_t output_size = 1 + (unsigned)snprintf(NULL, 0, json_format, tag, date_str, title);
	formatted_output = smalloc(output_size);

	snprintf(formatted_output, output_size, json_format, tag, date_str, title);
	printf("%s\n", formatted_output);	/* print the format to stdout */
	free(formatted_output);
	free(date_str);

	return;
}
