#include "main.h"

/**
 * print_pointer - a pointer variable
 * @list: arg pointer
 * @buffer: Buffer array
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: void
 */
int print_pointer(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int index = BUFF_SIZE - 2, len = 2, padd_start = 1; /* len=2, for '0x' */
	unsigned long n_address;
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(list, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	n_address = (unsigned long)address;

	while (n_address > 0)
	{
		buffer[index--] = map_to[n_address % 16];
		n_address /= 16;
		len++;
	}

	if ((flags & Flag_ZERO) && !(flags & Flag_MINUS))
		padd = '0';
	if (flags & Flag_PLUS)
		extra_c = '+', len++;
	else if (flags & Flag_SPACE)
		extra_c = ' ', len++;

	index++;

	return (write_pointer(buffer, index, len,
		width, flags, padd, extra_c, padd_start));
}

/**
 * print_unprintable - codes of non printable chars
 * @list: arg list
 * @buffer: Buffer array
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: void
 */
int print_unprintable(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int s = 0, offset = 0;
	char *str = va_arg(list, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[s] != '\0')
	{
		if (is_printable(str[s]))
			buffer[s + offset] = str[s];
		else
			offset += append_hexa_code(str[s], buffer, s + offset);

		s++;
	}

	buffer[s + offset] = '\0';

	return (write(1, buffer, s + offset));
}

/**
 * print_rev - reverse string
 * @list: arg pointer
 * @buffer: Buffer array
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: void
 */

int print_rev(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int s, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(list, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (s = 0; str[s]; s++)
		;

	for (s = s - 1; s >= 0; s--)
	{
		char u = str[s];

		write(1, &u, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13str - string in rot13.
 * @list: arg pointer
 * @buffer: Buffer array
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: void
 */
int print_rot13str(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	char a;
	char *str;
	unsigned int n, m;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(list, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (n = 0; str[n]; n++)
	{
		for (m = 0; in[m]; m++)
		{
			if (in[m] == str[n])
			{
				a = out[m];
				write(1, &a, 1);
				count++;
				break;
			}
		}
		if (!in[m])
		{
			a = str[n];
			write(1, &a, 1);
			count++;
		}
	}
	return (count);
}




