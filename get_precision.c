#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @fmt: formatted string in which to print the arguments
 * @s: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *fmt, int *s, va_list list)
{
	int curr_s = *s + 1;
	int precision = -1;

	if (fmt[curr_s] != '.')
		return (precision);

	precision = 0;

	for (curr_s += 1; fmt[curr_s] != '\0'; curr_s++)
	{
		if (is_digit(fmt[curr_s]))
		{
			precision *= 10;
			precision += fmt[curr_s] - '0';
		}
		else if (fmt[curr_s] == '*')
		{
			curr_s++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*s = curr_s - 1;

	return (precision);
}
