#include "shell.h"

/**
 * History - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int History(info_t *inf)
{
	print_list(inf->history);
	return (0);
}

/**
 * al_unset - sets alias to string
 * @inf: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int al_unset(info_t *inf, char *string)
{
	char *ptr, charac;
	int result;

	ptr = _strchr(string, '=');
	if (!ptr)
		return (1);
	charac = *ptr;
	*ptr = 0;
	result = delete_node_at_index(&(inf->alias),
		get_node_index(inf->alias, node_starts_with(inf->alias, string, -1)));
	*ptr = charac;
	return (result);
}

/**
 * al_set - sets alias to string
 * @inf: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int al_set(info_t *inf, char *string)
{
	char *ptr;

	ptr = _strchr(string, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (al_unset(inf, string));

	al_unset(inf, string);
	return (add_node_end(&(inf->alias), string, 0) == NULL);
}

/**
 * al_print - prints an alias string
 * @n: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int al_print(list_t *n)
{
	char *ptr = NULL, *a = NULL;

	if (n)
	{
		ptr = _strchr(n->str, '=');
		for (a = n->str; a <= ptr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * Alias - mimics the alias builtin (man alias)
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int Alias(info_t *inf)
{
	int ind = 0;
	char *ptr = NULL;
	list_t *n = NULL;

	if (inf->argc == 1)
	{
		n = inf->alias;
		while (n)
		{
			al_print(n);
			n = n->next;
		}
		return (0);
	}
	for (ind = 1; inf->argv[ind]; ind++)
	{
		ptr = _strchr(inf->argv[ind], '=');
		if (ptr)
			al_set(inf, inf->argv[ind]);
		else
			al_print(node_starts_with(inf->alias, inf->argv[ind], '='));
	}

	return (0);
}
