#include "shell.h"

/**
 * Exit - exits the shell
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int Exit(info_t *inf)
{
	int check_exit;

	if (inf->argv[1])
	{
		check_exit = erroratoi(inf->argv[1]);
		if (check_exit == -1)
		{
			inf->status = 2;
			error_print(inf, "Illegal number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_num = erroratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * CD - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int CD(info_t *inf)
{
	char *str, *directory, buffer[1024];
	int chdir_res;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		directory = _getenv(inf, "HOME=");
		if (!directory)
			chdir_res = /* TODO: what should this be? */
				chdir((directory = _getenv(inf, "PWD=")) ? directory : "/");
		else
			chdir_res = chdir(directory);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		chdir_res = /* TODO: what should this be? */
			chdir((directory = _getenv(inf, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_res = chdir(inf->argv[1]);
	if (chdir_res == -1)
	{
		error_print(inf, "can't change dir to ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * Help - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int Help(info_t *inf)
{
	char **args;

	args = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*args); /* temp att_unused workaround */
	return (0);
}
