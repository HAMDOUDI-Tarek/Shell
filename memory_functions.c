#include "shell.h"

/**
 * *_memset - fills memory with a constant byte.
 * @s: memory area.
 * @b: char to copy.
 * @n: Byte size.
 * Return: memory area.
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}

	return (s);
}

/**
 * _realloc - reallocates a memory.
 * @ptr: first memory.
 * @old_size: old memory size.
 * @new_size: new memory size.
 * Return: ptr.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		ptr = malloc(new_size);
	if (new_size == old_size)
		return (ptr);
	free(ptr);
	ptr = malloc(new_size);
	if (ptr == 0)
	{
		free(ptr);
		return (NULL);
	}

	return (ptr);
}

/**
 * str_free - frees a string of strings.
 * @str: string of strings.
 */
void str_free(char **str)
{
	char **ptr = str;

	if (!str)
		return;
	while (*str)
		free(*str++);
	free(ptr);
}
