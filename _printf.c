#include "main.h"

void print_buff(char buffer[], int *buffer_index);

/**
 * _printf - function
 * @format: character string
 * Return: void
 */
int _printf(const char *format, ...)
{
	int n, p = 0, p_c = 0;
	int flags, width, precision, size, buffer_index = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (n = 0; format && format[n] != '\0'; n++)
	{
		if (format[n] != '%')
		{
			buffer[buffer_index++] = format[n];
			if (buffer_index == BUFF_SIZE)
				print_buff(buffer, &buffer_index);
			/* write(1, &format[n], 1);*/
			p_c++;
		}
		else
		{
			print_buff(buffer, &buffer_index);
			flags = get_flags(format, &n);
			width = get_width(format, &n, list);
			precision = get_precision(format, &n, list);
			size = get_size(format, &n);
			++n;
			p = handle(format, &n, list, buffer,
				flags, width, precision, size);
			if (p == -1)
				return (-1);
			p_c += p;
		}
	}

	print_buff(buffer, &buffer_index);

	va_end(list);

	return (p_c);
}

/**
 * print_buff - Prints the buffer
 * @buffer: Array of chars
 * @buffer_index: the length.
 */
void print_buff(char buffer[], int *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buffer[0], *buffer_index);

	*buffer_index = 0;
}


