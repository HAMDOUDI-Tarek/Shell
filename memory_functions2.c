#include "shell.h"

/**
 * ptr_free - free pointer.
 * @ptr: pointer.
 * Return: 1 or 0.
 */
int ptr_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
