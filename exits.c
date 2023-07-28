#include "shell.h"

/**
 * custom_strncpy - copies a string up to 'n' characters
 * @dest: The destination string to be copied to
 * @src: The source string
 * @n: The number of characters to be copied
 * Return: The pointer to the destination string
 */
char *custom_strncpy(char *dest, char *src, int n)
{
	int i;
	char *result = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}

	if (i < n)
	{
		while (i < n)
		{
			dest[i] = '\0';
			i++;
		}
	}
	return (result);
}

/**
 * custom_strncat - concatenates two strings up to 'n' characters
 * @dest: The first string
 * @src: The second string
 * @n: The maximum number of bytes to be used
 * Return: The pointer to the concatenated string
 */
char *custom_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *result = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	if (j < n)
		dest[i] = '\0';

	return (result);
}

/**
 * custom_strchr - locates a character in a string
 * @s: The string to be parsed
 * @c: The character to look for
 * Return: A pointer to the first occurrence of 'c' in 's', or NULL if not found
 */
char *custom_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
