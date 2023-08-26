#include "main.h"

void print_arr(char **arr)
{
	size_t i = 0;

	if (!arr || !*arr)
		return;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		++i;
	}
	fflush(stdout);
}

/**
 * main - execve example
 * @arc: number of argument
 * @arv: pointer to argument
 * @environ: pointer to environment
 * Return: Always 0.
 */
int main(__attribute__((unused))int arc, __attribute__((unused)) char **arv,
		char *_environ[])
{
	int i = 0, status = 0, is_interactive = 0;
	char **argv = NULL, **commands = NULL, *lineptr = NULL, **stat = NULL;
	size_t n = 0, bytes_read = 0;
	list_t *env = NULL;

	env = _cpy_environ(_environ);		
	is_interactive = isatty(STDIN_FILENO);
	while (1)
	{
		if (is_interactive)
			write(STDOUT_FILENO, "#cisfun$ ", 10);
		bytes_read = getline(&lineptr, &n, stdin);
		if (bytes_read == ULLONG_MAX)
		{
			if (is_interactive)
				write(1, "\n", 1);
			free(lineptr);
			break;
		}
		
		i = 0;
		commands = get_commands(lineptr);
		free(lineptr);
		lineptr = NULL;
		print_arr(commands);
/*
		while (commands && commands[i] != NULL)
		{
			argv = get_argv(commands[i]);
			if (argv == NULL)
				continue;
			if (check_builtin(argv, env) == 98)
			{	
				stat = check_path(env, argv, &status);
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
		}*/
		_free_arr(commands);
	}
	_free_environ(env);
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

