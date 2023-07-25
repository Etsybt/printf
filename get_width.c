#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @fmt: Formatted string in which to print the arguments.
 * @s: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *fmt, int *s, va_list list)
{
	int curr_s;
	int width = 0;

	for (curr_s = *s + 1; fmt[curr_s] != '\0'; curr_s++)
	{
		if (is_digit(fmt[curr_s]))
		{
			width *= 10;
			width += fmt[curr_s] - '0';
		}
		else if (fmt[curr_s] == '*')
		{
			curr_s++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*s = curr_s - 1;

	return (width);
}
