#include "shell.h"

/**
 * _strlen - returns the length of a string.
 * @s:string.
 * Return: length.
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
	{
	}

	return (i);
}

/**
 * _strcmp - compares two strings.
 * @s1: first string.
 * @s2: second string.
 * Return: Always 0 (success).
 * another number if not.
 */

int _strcmp(char *s1, char *s2)
{
	int i, res;

	i = res = 0;

	while (res == 0)
	{
		if ((*(s1 + i) == '\0') && (*(s2 + i) == '\0'))
			break;
		res = *(s1 + i) - *(s2 + i);
		i++;
	}

	return (res);
}

/**
 * check_prefix - checks if text starts with prefix.
 * @text: string to look in.
 * @prefix: string to look for.
 * Return: address of next char of prefix or NULL.
 */
char *check_prefix(const char *text, const char *prefix)
{
	while (*prefix)
		if (*prefix++ != *text++)
			return (NULL);
	return ((char *)text);
}

/**
 * _strcat - concatenates two strings.
 * @dest: destination.
 * @src: source.
 * Return: destination.
 */
char *_strcat(char *dest, char *src)
{
	int counter, i;

	counter = i = 0;

	for (counter = 0; dest[counter]; counter++)
	{
	}

	for (i = 0; src[i]; i++)
	{
		dest[counter] = src[i];
		counter++;
	}
	return (dest);
}
