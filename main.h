#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

#define Flag_MINUS 1
#define Flag_PLUS 2
#define Flag_ZERO 4
#define Flag_HASH 8
#define Flag_SPACE 16

#define Size_L 2
#define Size_S 1

/**
 * struct format - Struct
 *
 * @format: format
 * @f: function
 */
struct format
{
	char format;
	int (*f)(va_list, char[], int, int, int, int);
};


/**
 * format format_t - Struct
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle(const char *format, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);

/* Funtions c, str */
int print_char(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int print_str(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int print_percent(va_list list, char buffer[],
	int flags, int width, int precision, int size);

/* Functions numbers */
int print_int(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int print_binary(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int print_unsigned(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int print_octal(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int print_hexadecimal(va_list list, char buffer[],
	int flags, int width, int precision, int size);
int print_hexa_upper(va_list list, char buffer[],
	int flags, int width, int precision, int size);

int print_hexa(va_list list, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Function to print non printable characters */
int print_unprintable(va_list list, char buffer[],
	int flags, int width, int precision, int size);

/* Funcion to print memory address */
int print_address(va_list list, char buffer[],
	int flags, int width, int precision, int size);

/* specifiers */
int get_flags(const char *fmt, int *s);
int get_width(const char *fmt, int *s, va_list list);
int get_precision(const char *fmt, int *s, va_list list);
int get_size(const char *fmt, int *s);

/* str in rev */
int print_rev(va_list list, char buffer[],
	int flags, int width, int precision, int size);

/* str rot13 */
int print_rot13str(va_list list, char buffer[],
	int flags, int width, int precision, int size);

/* width handler */
int handle_w_c(char a, char buffer[],
	int flags, int width, int precision, int size);
int write_number(int is_positive, int i, char buffer[],
	int flags, int width, int precision, int size);
int write_num(int i, char bff[], int flags, int width, int precision,
	int len, char padd, char extra_c);
int write_pnt(char buffer[], int i, int len,
	int width, int flags, char padd, char extra_c, int padd_start);

int write_und(int is_negative, int i,
char buffer[],
	int flags, int width, int precision, int size);

int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_num(long int n, int size);
long int convert_und(unsigned long int n, int size);

#endif

