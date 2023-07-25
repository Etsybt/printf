#include "main.h"

/**
 * print_char - Prints a character
 * @list: arg pointer
 * @buffer: Buffer array to handle print
 * @flags: flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: void
 */
int print_char(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	char a = va_arg(list, int);

	return (handle_w_c(a, buffer, flags, width, precision, size));
}

/**
 * print_str - a string
 * @list: arg pointer
 * @buffer: Buffer array to handle print
 * @flags: flags
 * @width: width.
 * @precision: Precision
 * @size: Size
 * Return: void
 */
int print_str(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, s;
	char *str = va_arg(list, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & Flag_MINUS)
		{
			write(1, &str[0], len);
			for (s = width - len; s > 0; s--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (s = width - len; s > 0; s--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}

	return (write(1, str, len));
}


/**
 * print_percent - a percent sign
 * @list: arg pointer
 * @buffer: Buffer array to handle print
 * @flags: flags
 * @width: width.
 * @precision: Precision
 * @size: Size
 * Return:void
 */
int print_percent(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(list);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}


/**
 * print_int - Prints integer
 * @list: arg pointer
 * @buffer: Buffer array to handle print
 * @flags: flags
 * @width: width.
 * @precision: Precision
 * @size: size
 * Return: void
 */
int print_int(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int b = BUFF_SIZE - 2;
	int is_negative = 0;
	long int i = va_arg(list, long int);
	unsigned long int num;

	i = convert_num(i, size);

	if (i == 0)
		buffer[b--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)i;

	if (i < 0)
	{
		num = (unsigned long int)((-1) * i);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[b--] = (num % 10) + '0';
		num /= 10;
	}

	b++;

	return (write_number(is_negative, b, buffer, flags, width, precision, size));
}


/**
 * prnt_binary - a binary num
 * list: arg pointer
 * @buffer: Buffer array to handle print
 * @flags: flags
 * @width: width.
 * @precision: Precision
 * @size: specifier
 * Return: void
 */
int print_binary(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int b, n, s, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	b = va_arg(list, unsigned int);
	n = 2147483648; /* (2 ^ 31) */
	a[0] = b / n;
	for (s = 1; s < 32; s++)
	{
		n /= 2;
		a[s] = (b / n) % 2;
	}
	for (s = 0, sum = 0, count = 0; s < 32; s++)
	{
		sum += a[s];
		if (sum || s == 31)
		{
			char u = '0' + a[s];

			write(1, &u, 1);
			count++;
		}
	}
	return (count);
}



