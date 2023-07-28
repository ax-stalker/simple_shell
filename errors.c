#include "shell.h"

/**
 * _custom_puts - Prints a string to the specified file descriptor
 * @str: The string to be printed
 * @fd: The file descriptor to write to
 *
 * Return: The number of characters written
 */
int _custom_puts(char *str, int fd)
{
	int i = 0;

	if (!str)
		return 0;
	while (*str)
	{
		i += _custom_putchar(*str++, fd);
	}
	return i;
}

/**
 * _custom_putchar - Writes the character c to the specified file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _custom_putchar(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return 1;
}
