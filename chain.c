#include "shell.h"

/**
 * Chain - check for chain delimiter.
 * @info: struct.
 * @buffer: buffer.
 * @position: current buffer.
 * Return: 0 or 1.
 */
int Chain(info_t *info, char *buffer, size_t *position)
{
	size_t index = *position;

	if (buffer[index] == '|' && buffer[index + 1] == '|')
	{
		buffer[index] = '\0';
		index++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[index] == '&' && buffer[index + 1] == '&')
	{
		buffer[index] = '\0';
		index++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[index] == ';')
	{
		buffer[index] = '\0';
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}

	*position = index;
	return (1);
}

/**
 * chainchecker - checks chain for delimiter.
 * @info: struct.
 * @buffer: buffer.
 * @position: position in buffer.
 * @current_index: buffer start.
 * @total_length: buffer length.
 */
void chainchecker(info_t *info, char *buffer, size_t *position,
		size_t current_index, size_t total_length)
{
	size_t index = *position;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[current_index] = '\0';
			index = total_length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[current_index] = '\0';
			index = total_length;
		}
	}

	*position = index;
}

/**
 * repal - replaces an alias.
 * @info: struct.
 * Return: 0 or 1.
 */
int repal(info_t *info)
{
	int attempt = 0;
	list_t *alias_node;
	char *equal_sign_position;

	while (attempt < 10)
	{
		alias_node = node_starts_with(info->alias, info->argv[0], '=');
		if (!alias_node)
			return (0);

		free(info->argv[0]);

		equal_sign_position = _strchr(alias_node->str, '=');
		if (!equal_sign_position)
			return (0);

		equal_sign_position = _strdup(equal_sign_position + 1);
		if (!equal_sign_position)
			return (0);

		info->argv[0] = equal_sign_position;
		attempt++;
	}

	return (1);
}

/**
 * repvar - replaces vars.
 * @info: struct.
 * Return: 0 or 1.
 */
int repvar(info_t *info)
{
	int index = 0;
	list_t *currentNode;

	for (index = 0; info->argv[index]; index++)
	{
		if (info->argv[index][0] != '$' || !info->argv[index][1])
			continue;

		if (!_strcmp(info->argv[index], "$?"))
		{
			replaceString(&(info->argv[index]),
					_strdup(convertNumber(info->status, 10, 0)));
			continue;
		}

		if (!_strcmp(info->argv[index], "$$"))
		{
			replaceString(&(info->argv[index]),
					_strdup(convertNumber(getpid(), 10, 0)));
			continue;
		}

		currentNode = findNode(info->env, &info->argv[index][1], '=');

		if (currentNode)
		{
			replaceString(&(info->argv[index]),
					_strdup(_strchr(currentNode->str, '=') + 1));
			continue;
		}

		replaceString(&info->argv[index], _strdup(""));
	}

	return (0);
}

/**
 * repstr - replaces string.
 * @old: old string.
 * @new: new string.
 * Return: 1.
 */
int repstr(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
