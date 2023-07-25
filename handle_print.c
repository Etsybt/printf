#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @i: i.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle(const char *format, int *i, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t format_types[] = {
		{'c', print_char}, {'s', print_str}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_address}, {'S', print_unprintable},
		{'r', print_rev}, {'R', print_rot13str}, {'\0', NULL}
	};
	for (i = 0; format_types[i].format != '\0'; i++)
		if (fmt[*i] == format_types[i].format)
			return (format_types[i].fn(list, buffer, flags, width, precision, size));

	if (format_types[i].format == '\0')
	{
		if (format[*i] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (format[*i - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*i);
			while (format[*i] != ' ' && format[*i] != '%')
				--(*i);
			if (format[*i] == ' ')
				--(*i);
			return (1);
		}
		unknow_len += write(1, &format[*i], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
