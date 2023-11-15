#include "shell.h"

/**
 * Exit - Handles the exit command in the shell.
 * @info: Struct.
 * Return: 0 or 1.
 */
int Exit(info_t *info)
{
	int exit_value = 0;

	if (info->argv[1])
	{
		exit_value = _erratoi(info->argv[1]);

		if (exit_value == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}

		info->err_num = exit_value;
	}
	else
	{
		info->err_num = -1;
	}

	return (-2);
}

/**
 * get_current_directory - gives out pwd.
 * @buffer: Buffer to store pwd.
 * Return: pwd.
 */
char *get_current_directory(char *buffer)
{
	char *cwd = getcwd(buffer, 1024);

	if (!cwd)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	return (cwd);
}

/**
 * change_directory - change pwd.
 * @info: Pointer to the info_t structure.
 * @new_dir: New directory path.
 * Return: 0 or 1.
 */
int change_directory(info_t *info, const char *new_dir)
{
	int chdir_ret = chdir(new_dir);

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(new_dir), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", get_current_directory(buffer));
	}

	return (chdir_ret);
}

/**
 * CD - Implementation of the "cd" command.
 * @info: struct.
 * Return: 0, 1 or -1.
 */
int CD(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = get_current_directory(buffer);

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = change_directory(info,
					(dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = change_directory(info, dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = change_directory(info,
				(dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
	{
		chdir_ret = change_directory(info, info->argv[1]);
	}

	return (chdir_ret == -1 ? -1 : 0);
}

/**
 * Help - changes process pwd.
 * @info: Struct.
 *  Return: Always 0
 */
int Help(info_t *info)
{
	char **args;

	args = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*args);
	return (0);
}
