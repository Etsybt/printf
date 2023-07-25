#include "main.h"

/**
 * get_flags - active flags
 * @fmt: Formatted string
 * @s: parameter.
 * Return: Flags
 */
int get_flags(const char *fmt, int *s)
{
	int i, curr_s;
	int flags = 0;
	const char FLAGS_CHar[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARRay[] = {Flag_MINUS, Flag_PLUS,
		Flag_ZERO, Flag_HASH, Flag_SPACE, 0};

	for (curr_s = *s + 1; fmt[curr_s] != '\0'; curr_s++)
	{
		for (i = 0; FLAGS_CHar[i] != '\0'; i++)
			if (fmt[curr_s] == FLAGS_CHar[i])
			{
				flags |= FLAGS_ARRay[i];
				break;
			}

		if (FLAGS_CHar[i] == 0)
			break;
	}

	*s = curr_s - 1;

	return (flags);
}


