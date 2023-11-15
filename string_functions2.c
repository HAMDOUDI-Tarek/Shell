#include "shell.h"
/**
 * *_strcpy - copies string into another.
 *@src: pointer.
 *@dest: pointer.
 *Return: the pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
	int len, i;

	for (len = 0; src[len]; len++)
	{
	}

	for (i = 0; i <= len ; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

/**
 * _strdup - allocates space in memory for a string.
 * @str: string.
 * Return: duplicated string.
 */

char *_strdup(char *str)
{
	char *dup;
	int i = 0, len = 0;

	if (str == NULL)
		return (NULL);

	while (*(str + i))
		len++, i++;
	len++;

	dup = malloc(sizeof(char) * len);

	if (dup == NULL)
		return (NULL);

	i = 0;
	while (i < len)
	{
		*(dup + i) = *(str + i);
		i++;
	}

	return (dup);
}

/**
 *_puts - prints string.
 *@str: string.
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	for (i = 0; str[i]; i++)
	{
		_putchar(str[i]);
	}
}

/**
 *_putchar - writes the character c to stdout
 *@c: The character to print
 *Return: 1 or -1.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
