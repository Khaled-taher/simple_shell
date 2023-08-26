#include "main.h"

/**
 * check_builtin - selects the correct function to perform the operation
 * @argv: argument of command
 * @env: pointer to system environment
 * Return: 0 if succees and 98 if not found and -1 in error and -2 if exit
 */
int check_builtin(char **argv, list_t **env, int *status)
{
	if (!_strcmp(argv[0], "env"))
	{
		if (argv[1] == NULL)
		{
			_print_environ(*env);
			*status = 0;
			return (0);
		}
		write(STDERR_FILENO, "Error", 5);
		*status = 127;
		return (-1);
	}
	if (!_strcmp(argv[0], "exit"))
	{
		if (argv[1] == NULL)
			return (-2);
		else if (argv[1] != NULL && argv[2] == NULL && is_num(argv[1]) == 1)
		{
			*status = _atoi(argv[1]);
			return (-2);
		}
		else
		{
			*status = 2;
			return (0);
		}
	}/*
	if (!_strcmp(argv[0], "setenv"))
	{
		if (argv[1] != NULL && argv[2] != NULL && argv[3] == NULL)
		{
			return (_setenv(*env, argv[1], argv[2], 1));
		}
		write(STDERR_FILENO, "Error", 5);
		*status = 127;
		return (-1);
	}*/
	return (check_builtin_helper(argv, env, status));
}

/**
 * check_builtin_helper - selects the correct function to perform the operation
 * @argv: argument of command
 * @env: pointer to system environment
 * Return: 0 if succees and 98 if not found and -1 in error
 */
int check_builtin_helper(char **argv, list_t **env, int *status)
{
	if  (_strcmp(argv[0], "unsetenv") == 0)
	{
		if (argv[1] != NULL && argv[2] == NULL)
			return (_unsetenv(*env, argv[1]));
		write(STDERR_FILENO, "Error", 5);
		*status = 127;
		return (-1);
	}
	return (98);
}

/**
 * is_num - check if string in all digits
 * @str: str to be checked
 * Return: 1 if succees and -1 in fail
 */
int is_num(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			continue;
		else
			return (-1);
	}
	return (1);

}

