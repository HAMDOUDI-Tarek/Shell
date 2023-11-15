#include "shell.h"

/**
 * History - displays the history list.
 * @info: Struct.
 *  Return: Always 0.
 */
int History(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * al_unset - sets alias.
 * @info: struct
 * @al: Alias.
 * Return: 0 or 1.
 */
int al_unset(info_t *info, char *al)
{
	char *ptr, cr;
	int result;

	ptr = _strchr(al, '=');
	if (!ptr)
		return (1);
	cr = *ptr;
	*ptr = 0;
	result = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, al, -1)));
	*ptr = cr;
	return (result);
}

/**
 * al_set - sets alias.
 * @info: struct.
 * @al: Alias.
 * Return: 0 or 1.
 */
int al_set(info_t *info, char *al)
{
	char *ptr;
	int result;

	ptr = _strchr(al, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, al));

	unset_alias(info, al);
	result = (add_node_end(&(info->alias), al, 0) == NULL);
	return (result);
}

/**
 * al_print - prints alias.
 * @node: alias node.
 * Return: 0 or 1.
 */
int al_print(list_t *node)
{
	char *ptr = NULL, *b = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (b = node->str; b <= ptr; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * Alias - like alias function.
 * @info: Struct.
 *  Return: Always 0
 */
int Alias(info_t *info)
{
	int argIndex = 0;
	char *equalSignPtr = NULL;
	list_t *aliasNode = NULL;

	if (info->argc == 1)
	{
		aliasNode = info->alias;
		while (aliasNode)
		{
			print_alias(aliasNode);
			aliasNode = aliasNode->next;
		}
		return (0);
	}

	for (argIndex = 1; info->argv[argIndex]; argIndex++)
	{
		equalSignPtr = _strchr(info->argv[argIndex], '=');
		if (equalSignPtr)
		{
			set_alias(info, info->argv[argIndex]);
		}
		else
		{
			print_alias(node_starts_with(info->alias, info->argv[argIndex], '='));
		}
	}

	return (0);
}

