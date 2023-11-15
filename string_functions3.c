#include "shell.h"

/**
 * _strncpy - copies a string.
 * @dest: destination.
 * @src: source.
 * @n: byte number.
 * Return: destination.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i]; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}

/**
 * _strncat - concatenate 2 strings.
 * @dest: destination.
 * @src: source.
 * @n: byte number.
 * Return: destination.
 */
char *_strncat(char *dest, char *src, int n)
{
	int counter1, counter2;

	counter1 = counter2 = 0;
	for (counter1 = 0; src[counter1]; counter1++)
	{
	}

	while (counter2 < n)
	{
		*(dest + counter1) = *(src + counter2);
		if (*(src + counter2) == '\0')
			break;
		counter1++;
		counter2++;
	}

	dest[counter1] = '\0';
	return (dest);
}

/**
 **_strchr - locates a character in a string.
 *@str: the string to look in.
 *@charac: the character to look for.
 *Return: area.
 */
char *_strchr(char *str, char charac)
{
	while (*str++)
	{
		if (*str == charac)
			return (str);
	}

	return (NULL);
}
