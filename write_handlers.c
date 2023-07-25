#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_w_c - Prints a string
 * @a: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_w_c(char a, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and paddind at buffer's right */
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & Flag_ZERO)
		padd = '0';

	buffer[i++] = a;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & Flag_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_positive: Lista of arguments
 * @i: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_positive, int i, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - i - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & Flag_ZERO) && !(flags & Flag_MINUS))
		padd = '0';
	if (is_positive)
		extra_ch = '-';
	else if (flags & Flag_PLUS)
		extra_ch = '+';
	else if (flags & Flag_SPACE)
		extra_ch = ' ';

	return (write_num(i, buffer, flags, width, precision,
		length, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @i: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int i, char buffer[],
	int flags, int width, int precision,
	int len, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (precision == 0 && i == BUFF_SIZE - 2 && buffer[i] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (precision == 0 && i == BUFF_SIZE - 2 && buffer[i] == '0')
		buffer[i] = padd = ' '; /* width is displayed with padding ' ' */
	if (precision > 0 && precision < len)
		padd = ' ';
	while (precision > len)
		buffer[--i] = '0', len++;
	if (extra_c != 0)
		len++;
	if (width > len)
	{
		for (i = 1; i < width - len + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & Flag_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--i] = extra_c;
			return (write(1, &buffer[i], len) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & Flag_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--i] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[i], len));
		}
		else if (!(flags & Flag_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[i], len - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--i] = extra_c;
	return (write(1, &buffer[i], len));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @i: iex at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_und(int is_negative, int i,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - i - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && i == BUFF_SIZE - 2 && buffer[i] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--i] = '0';
		length++;
	}

	if ((flags & Flag_ZERO) && !(flags & Flag_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & Flag_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[i], length) + write(1, &buffer[0], i));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[i], length));
		}
	}

	return (write(1, &buffer[i], length));
}

/**
 * write_pnt - Write a memory address
 * @buffer: Arrays of chars
 * @i: Index at which the number starts in the buffer
 * @len: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pnt(char buffer[], int i, int len,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > len)
	{
		for (i = 3; i < width - len + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & Flag_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--i] = 'x';
			buffer[--i] = '0';
			if (extra_c)
				buffer[--i] = extra_c;
			return (write(1, &buffer[i], len) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & Flag_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--i] = 'x';
			buffer[--i] = '0';
			if (extra_c)
				buffer[--i] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[i], len));
		}
		else if (!(flags & Flag_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[i], len - (1 - padd_start) - 2));
		}
	}
	buffer[--i] = 'x';
	buffer[--i] = '0';
	if (extra_c)
		buffer[--i] = extra_c;
	return (write(1, &buffer[i], BUFF_SIZE - i - 1));
}
