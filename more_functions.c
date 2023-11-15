#include "shell.h"

/**
 * is_interactive - checks if shell is interactive.
 * @info: struct.
 * Return: 0 or 1.
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * delimeter - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int delimeter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 *_atoi - converts a string to an integer.
 *@str: string.
 *Return: number.
 */
int _atoi(char *str)
{
	int k;

	if (str[0] == '-')
		k = 1;
	else
		k = 0;

	int count, times = 1;

	for (count = 0; str[count] != '\0'; count++)
	{
		times *= 10;
	}

	int i, j;
	int res = 0;

	if (k)
		times /= 100;
	else
		times /= 10;

	for (i = k; i < count; i++)
	{
		j = (str[i] - '0') * times;
		res += j;
		times /= 10;
	}
	if (k)
		return (res * -1);
	return (res);
}
