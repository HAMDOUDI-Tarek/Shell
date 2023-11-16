#include "shell.h"

/**
 * Chain - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @buffer: the char buffer
 * @ptr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int Chain(info_t *inf, char *buffer, size_t *ptr)
{
	size_t i = *ptr;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buffer[i] == ';') /* found end of this command */
	{
		buffer[i] = 0; /* replace semicolon with null */
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = i;
	return (1);
}

/**
 * chainchecker - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @buffer: the char buffer
 * @ptr: address of current position in buf
 * @j: starting position in buf
 * @len: length of buf
 */
void chainchecker(info_t *inf, char *buffer, size_t *ptr, size_t j, size_t len)
{
	size_t i = *ptr;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buffer[j] = 0;
			i = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buffer[j] = 0;
			i = len;
		}
	}

	*ptr = i;
}

/**
 * rep_al - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int rep_al(info_t *inf)
{
	int ind;
	list_t *n;
	char *ptr;

	for (ind = 0; ind < 10; ind++)
	{
		n = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!n)
			return (0);
		free(inf->argv[0]);
		ptr = _strchr(n->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		inf->argv[0] = ptr;
	}
	return (1);
}

/**
 * rep_vars - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rep_vars(info_t *inf)
{
	int ind = 0;
	list_t *n;

	for (ind = 0; inf->argv[ind]; ind++)
	{
		if (inf->argv[ind][0] != '$' || !inf->argv[ind][1])
			continue;

		if (!_strcmp(inf->argv[ind], "$?"))
		{
			rep_str(&(inf->argv[ind]),
				_strdup(num_conv(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[ind], "$$"))
		{
			rep_str(&(inf->argv[ind]),
				_strdup(num_conv(getpid(), 10, 0)));
			continue;
		}
		n = node_starts_with(inf->env, &inf->argv[ind][1], '=');
		if (n)
		{
			rep_str(&(inf->argv[ind]),
				_strdup(_strchr(n->str, '=') + 1));
			continue;
		}
		rep_str(&inf->argv[ind], _strdup(""));

	}
	return (0);
}

/**
 * rep_str - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int rep_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
