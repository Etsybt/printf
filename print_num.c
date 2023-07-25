#include "main.h"

/**
 * print_unsigned - unsigned int
 * @list: arg pointer
 * @buffer: Buffer array
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: void
 */
int print_unsigned(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int b = BUFF_SIZE - 2;
	unsigned long int n = va_arg(list, unsigned long int);

	n = convert_und(n, size);

	if (n == 0)
		buffer[b--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (n > 0)
	{
		buffer[b--] = (n % 10) + '0';
		n /= 10;
	}

	b++;

	return (write_und(0, b, buffer, flags, width, precision, size));

}

/**
 * print_octal - int in octal notation
 * @list: arg pointer
 * @buffer: Buffer array
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: void
 */
int print_octal(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{

	int b = BUFF_SIZE - 2;
	unsigned long int n = va_arg(list, unsigned long int);
	unsigned long int init_n = n;

	UNUSED(width);

	n = convert_und(n, size);

	if (n == 0)
		buffer[b--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (n > 0)
	{
		buffer[b--] = (n % 8) + '0';
		n /= 8;
	}

	if (flags & Flag_HASH && init_n != 0)
		buffer[b--] = '0';

	b++;

	return (write_und(0, b, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - int in hexadecimal notation
 * @list: arg pointer
 * @buffer: Buffer array
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: void
 */
int print_hexadecimal(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(list, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - int in upper hexadecimal notation
 * @list: arg pointer
 * @buffer: Buffer array
 * @flags: flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: void
 */
int print_hexa_upper(va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(list, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - hexadecimal int in lower or upper
 * @list: arg pointer
 * @map_to: Array of values
 * @buffer: Buffer array
 * @flags: flags
 * @flag_ch: active flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * @size: Size spec
 * Return: void
 */
int print_hexa(va_list list, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int b = BUFF_SIZE - 2;
	unsigned long int n = va_arg(list, unsigned long int);
	unsigned long int init_n = n;

	UNUSED(width);

	n = convert_und(n, size);

	if (n == 0)
		buffer[b--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (n > 0)
	{
		buffer[b--] = map_to[n % 16];
		n /= 16;
	}

	if (flags & Flag_HASH && init_n != 0)
	{
		buffer[b--] = flag_ch;
		buffer[b--] = '0';
	}

	b++;

	return (write_und(0, b, buffer, flags, width, precision, size));
}

