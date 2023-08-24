#include "main.h"

/**
 * main - execve example
 * @arc: number of argument
 * @arv: pointer to argument
 * @environ: pointer to environment
 * Return: Always 0.
 */
int main(__attribute__((unused))int arc, __attribute__((unused)) char **arv,
		char *environ[])
{
	int i = 0, status = 0;
	char **argv, **command, *lineptr, **stat;
	size_t n;
	list_t *env = NULL;

	env = _cpy_environ(environ);
	_getline(&lineptr, &n, stdin);
	if (_strcmp("exit\n", lineptr) == 0)
		exit(0);
	
	while (1)
	{	write(STDOUT_FILENO,"#cisfun$ ",10);
		if (_getline(&lineptr, &n, stdin) == -1)
		{
			perror("error:");
			continue;
		}
		i = 0;
		command = get_command(lineptr);
		if (command == NULL)
			continue;
		while (command[i] != NULL)
		{
			argv = get_argv(command[i]);
			if (argv == NULL)
				continue;
			if (check_builtin(argv, env) == 98)
			{	stat = check_path(env, argv, &status);
				if (status == 0)
				{
					fork_proc(stat, env);
					_free_arr(stat);
				}
				else if (status == 98)
					printf("%s: command not found\n", argv[0]);
				else
					perror("Error:");
			}
			i++;
			_free_arr(argv);
		}
		_free_arr(command);
	}
	return (0);
}

/**
 * fork_proc - creat child to run a coomand
 * @argv: argument passed to new process
 * @env: pointer to environment
 * Return: always (0)
 */
int fork_proc(char **argv, list_t *env)
{
	pid_t pid;
	int status = 0;

	pid = fork();
	if (pid < 0)
	{
		perror("Error:");
		return (0);
	}
	if (pid == 0)
	{
		if (execve(argv[0], argv, list_to_arr(env)) == -1)
		{
			perror("Error:");
			return (0);
		}
	}
	else
	{
		wait(&status);
	}
	return (0);
}

/**
 * _free_arr - to free array
 * @arr: pointer to environment variables
 *
 * Return: nothing
 */
void _free_arr(char **arr)
{
	int i = 0;
	
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

