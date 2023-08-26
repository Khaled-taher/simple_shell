#include "main.h"

/**
* print_error - print error
* @line_number: line number
* @p_name: program name
* @argv: argv
*/
void print_error(int line_number, char *p_name, char **argv)
{
	char *line_n = NULL;

	write(STDERR_FILENO, p_name, _strlen(p_name));
	write(STDERR_FILENO, ": ", 2);
	line_n = unsigned_to_str(line_number);
	write(STDERR_FILENO, line_n, _strlen(line_n));
	free(line_n);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": not found\n", 12);
}
/**
* execute_commands - execute commands
* @status: status
* @commands: commands
* @env: env
* @line_number: line number
* @p_name: p name
* Return: return
*/
int execute_commands(int *status, char **commands, list_t **env,
				int line_number, char *p_name)
{
	size_t i = 0;
	int is_built = 0;
	char **argv = NULL, *path = NULL;

	while (commands && commands[i])
	{
		argv = get_argv(commands[i]);
		if (argv == NULL)
			continue;
		is_built = check_builtin(argv, env, status);
		if (is_built == -2) /* exit */
		{
			free(argv);
			return (0);
		}
		if (is_built == 98) /* Not our built in */
		{
			path = get_path(*env, argv, status);
			if (path)
				fork_proc(path, argv, *env, status);
			else
				print_error(line_number, p_name, argv);
			free(path);
		}
		free(argv);
		i++;
	}
	return (1);
}

/**
 * main - execve example
 * @arc: number of argument
 * @argv: pointer to argument
 * @_environ: pointer to environment
 * Return: Always 0.
 */
int main(__attribute__((unused))int arc, __attribute__((unused)) char **argv,
		char *_environ[])
{
	int status = 0, is_interactive = 0, result = 0, line_num = 1;
	char **commands = NULL, *lineptr = NULL;
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
		commands = get_commands(lineptr);
		free(lineptr);
		lineptr = NULL;
		if (!commands)
			break;
		result = execute_commands(&status, commands, &env, line_num++, argv[0]);
		_free_arr(commands);
		if (!result)
			break;
	}
	_free_environ(env);
	return (status);
}

/**
* fork_proc - creat child to run a coomand
* @argv: argument passed to new process
* @env: pointer to environment
* @path: path
* @status: status
* Return: always (0)
*/
int fork_proc(char *path, char **argv, list_t *env, int *status)
{
	int pid = 0, i = 0;
	char **_env = NULL;

	_env = list_to_arr(env);
	pid = fork();
	if (pid < 0)
	{
		write(STDERR_FILENO, "ERROR\n", 6);
		return (0);
	}
	if (pid == 0)
	{
		execve(path, argv, _env);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, status, 0);
	*status = WEXITSTATUS(*status);
	while (_env[i])
		free(_env[i++]);
	free(_env);
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

