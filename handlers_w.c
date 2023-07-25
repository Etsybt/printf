#include "main.h"

/**
 * handle_write_char - Prints a string
 * @a: char types.
 * @buffer: Buffer array
 * @flags: flags.
 * @width: width.
 * @precision: precision
 * @size: Size
 * Return: void
 */
int handle_w_c(char a, char buffer[],
	int flags, int width, int precision, int size)
{
	int s = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & Flag_ZERO)
		padd = '0';

	buffer[s++] = a;
	buffer[s] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (s = 0; s < width - 1; s++)
			buffer[BUFF_SIZE - s - 2] = padd;

		if (flags & Flag_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - s - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - s - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @i: char types.
 * @buffer: Buffer array
 * @flags: flags
 * @width: width.
 * @precision: precision
 * @size: Size
 * Return:void
 */
int write_number(int is_negative, int i, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFF_SIZE - i - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & Flag_ZERO) && !(flags & Flag_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & Flag_PLUS)
		extra_ch = '+';
	else if (flags & Flag_SPACE)
		extra_ch = ' ';

	return (write_num(i, buffer, flags, width, precision,
		len, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @i: Index
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @len: length
 * @padd: Pading char
 * @extra_c: Extra char
 * Return: Number of printed chars.
 */
int write_num(int i, char buffer[],
	int flags, int width, int prec,
	int len, char padd, char extra_c)
{
	int s, padd_start = 1;

	if (prec == 0 && i == BUFF_SIZE - 2 && buffer[i] == '0' && width == 0)
		return (0);
	if (prec == 0 && i == BUFF_SIZE - 2 && buffer[i] == '0')
		buffer[i] = padd = ' ';
	if (prec > 0 && prec < len)
		padd = ' ';
	while (prec > len)
		buffer[--i] = '0', len++;
	if (extra_c != 0)
		len++;
	if (width > len)
	{
		for (s = 1; s < width - len + 1; s++)
			buffer[s] = padd;
		buffer[s] = '\0';
		if (flags & Flag_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--i] = extra_c;
			return (write(1, &buffer[i], len) + write(1, &buffer[1], s - 1));
		}
		else if (!(flags & Flag_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--i] = extra_c;
			return (write(1, &buffer[1], s - 1) + write(1, &buffer[i], len));
		}
		else if (!(flags & Flag_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], s - padd_start) +
				write(1, &buffer[i], len - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--i] = extra_c;
	return (write(1, &buffer[i], len));
}

/**
 * write_und - unsigned number
 * @is_negative: Number indicating if the num is negative
 * @i: Index
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: void
 */
int write_und(int is_negative, int i,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int len = BUFF_SIZE - i - 1, s = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && i == BUFF_SIZE - 2 && buffer[i] == '0')
		return (0);

	if (precision > 0 && precision < len)
		padd = ' ';

	while (precision > len)
	{
		buffer[--i] = '0';
		len++;
	}

	if ((flags & Flag_ZERO) && !(flags & Flag_MINUS))
		padd = '0';

	if (width > len)
	{
		for (s = 0; s < width - len; s++)
			buffer[s] = padd;

		buffer[s] = '\0';

		if (flags & Flag_MINUS)
		{
			return (write(1, &buffer[i], len) + write(1, &buffer[0], s));
		}
		else
		{
			return (write(1, &buffer[0], s) + write(1, &buffer[i], len));
		}
	}

	return (write(1, &buffer[i], len));
}

/**
 * write_pnt - Write a memory address
 * @buffer: Arrays of chars
 * @i: Index
 * @len: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 * Return: void
 */
int write_pnt(char buffer[], int i, int len,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int s;

	if (width > len)
	{
		for (s = 3; s < width - len + 3; s++)
			buffer[s] = padd;
		buffer[s] = '\0';
		if (flags & Flag_MINUS && padd == ' ')
		{
			buffer[--i] = 'x';
			buffer[--i] = '0';
			if (extra_c)
				buffer[--i] = extra_c;
			return (write(1, &buffer[i], len) + write(1, &buffer[3], s - 3));
		}
		else if (!(flags & Flag_MINUS) && padd == ' ')
		{
			buffer[--i] = 'x';
			buffer[--i] = '0';
			if (extra_c)
				buffer[--i] = extra_c;
			return (write(1, &buffer[3], s - 3) + write(1, &buffer[i], len));
		}
		else if (!(flags & Flag_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], s - padd_start) +
				write(1, &buffer[i], len - (1 - padd_start) - 2));
		}
	}
	buffer[--i] = 'x';
	buffer[--i] = '0';
	if (extra_c)
		buffer[--i] = extra_c;
	return (write(1, &buffer[i], BUFF_SIZE - i - 1));
}
