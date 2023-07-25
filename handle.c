#include "main.h"
/**
 * handle - Prints an argument based on its type
 * @fmt: Format
 * @list: arg pointer
 * @i: index
 * @buffer: Buffer array
 * @flags: flags
 * @width: width.
 * @precision: Precision
 * @size: Size
 * Return: 1 or 2;
 */
int handle(const char *fmt, int *i, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int n, unknow_len = 0, printed_chars = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_str}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_address},{'S', print_unprintable},
		{'r', print_rev}, {'R', print_rot13str}, {'\0', NULL}
	};
	for (n = 0; fmt_types[n].fmt != '\0'; n++)
		if (fmt[*i] == fmt_types[n].fmt)
			return (fmt_types[n].fn(list, buffer, flags, width, precision, size));

	if (fmt_types[n].fmt == '\0')
	{
		if (fmt[*i] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*i - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*i);
			while (fmt[*i] != ' ' && fmt[*i] != '%')
				--(*i);
			if (fmt[*i] == ' ')
				--(*i);
			return (1);
		}
		unknow_len += write(1, &fmt[*i], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
