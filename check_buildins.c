#include "main.h"

/**
 * check_builtin - selects the correct function to perform the operation
 * @argv: argument of command
 * @env: pointer to system environment
 * Return: 0 if succees and 98 if not found and -1 in error
 */
int check_builtin(char **argv, list_t *env)
{
	if (_strcmp(argv[0], "env") == 0)
	{
		if (argv[1] == NULL)
		{
			_print_environ(env);
			return (0);
		}
		errno = EINVAL;
		perror("Error:");
		return (-1);
	}
	if (_strcmp(argv[0], "exit") == 0)
	{
		if (argv[1] == NULL)
			_builtin_exit(0);
		else if (argv[1] != NULL && argv[2] == NULL && is_num(argv[1]) == 1)
		{
			if (argv[1][0] == '0')
				_builtin_exit(127);
			else
				_builtin_exit(_atoi(argv[1]));
		}
		else
			_builtin_exit(127);
	}
	if (_strcmp(argv[0], "setenv") == 0)
	{
		if (argv[1] != NULL && argv[2] != NULL && argv[3] == NULL)
		{
			return(_setenv(env, argv[1], argv[2], 1));
		}
		errno = EINVAL;
		perror("Error");
		return (-1);
	}
	return (check_builtin_helper(argv, env));
}

/**
 * check_builtin_helper - selects the correct function to perform the operation
 * @argv: argument of command
 * @env: pointer to system environment
 * Return: 0 if succees and 98 if not found and -1 in error
 */
int check_builtin_helper(char **argv, list_t *env)
{
	if  (_strcmp(argv[0], "unsetenv") == 0)
	{
		if (argv[1] != NULL && argv[2] == NULL)
			return (_unsetenv(env, argv[1]));
		errno = EINVAL;
		perror("Error");
		return (-1);
	}
	return (98); /* remove it after complete below code */
	if (_strcmp(argv[0], "cd") == 0)
	{
		/*if ((argv[1] == NULL || "~") && argv[2] == NULL)
		{
			chdir_home();
		}*/
		/*else if (argv[1] == "-" && argv[2] == NULL)
		{
			func to change dir to previous dir
		}
		else if (argv[1] != NULL && argv[2] == NULL)
		{
			func to change dir to argv[1]
		}
		else
		{
			errno = EINVAL;
			perror("Error");
			return (-1)
		}*/
	}
	return (0);
}

/**
 * check_builtin_helper2 - selects the correct function to perform the opration
 * @argv: argument of command
 * @env: pointer to system environment
 * Return: 0 if succees and 98 if not found and -1 in error
 */
/*
int check_builtin_helper2(char **argv, list_t *env)
{
	if (_strcmp(argv[0], "alias") == 0)
	{
	}
}
*/
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

