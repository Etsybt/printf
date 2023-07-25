#include "main.h"

/**
 * get_size - Calculates the size to cast the argument
 * @fmt: formatted string in which to print the arguments
 * @s: List of arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *fmt, int *s)
{
	int curr_s = *s + 1;
	int size = 0;

	if (fmt[curr_s] == 'l')
		size = Size_L;
	else if (fmt[curr_s] == 'h')
		size = Size_S;

	if (size == 0)
		*s = curr_s - 1;
	else
		*s = curr_s;

	return (size);
}
