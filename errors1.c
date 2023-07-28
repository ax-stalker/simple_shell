#include "shell.h"

/**
 * custom_atoi - converts a string to an integer
 * @s: The string to be converted
 * Return: The converted number on success, -1 on error
 */
int custom_atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++; /* Skip leading plus sign */

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return -1; /* Integer overflow */
		}
		else
			return -1; /* Non-numeric character found */
	}
	return (int)result;
}

/**
 * print_custom_error - prints an error message
 * @info: The parameter & return info struct
 * @error_str: String containing specified error type
 * Return: Nothing
 */
void print_custom_error(info_t *info, char *error_str)
{
	_eputs(info->fname);
	_eputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(error_str);
}

/**
 * print_decimal - Prints a decimal (integer) number (base 10)
 * @input: The input number
 * @fd: The file descriptor to write to
 * Return: Number of characters printed
 */
int print_decimal(int input, int fd)
{
	int (*custom_putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int absolute, current;

	if (fd == STDERR_FILENO)
		custom_putchar = _eputchar;

	if (input < 0)
	{
		absolute = -input;
		custom_putchar('-');
		count++;
	}
	else
		absolute = input;

	current = absolute;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute / i)
		{
			custom_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}

	custom_putchar('0' + current);
	count++;

	return count;
}

/**
 * custom_convert_number - Converter function, a clone of itoa
 * @num: Number to convert
 * @base: Base of the conversion
 * @flags: Argument flags
 *
 * Return: String representation of the converted number
 */
char *custom_convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return ptr;
}

/**
 * remove_shell_comments - Replaces the first instance of '#' with '\0'
 * @buf: Address of the string to modify
 * Return: Nothing
 */
void remove_shell_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
