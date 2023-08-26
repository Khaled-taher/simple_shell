#include "main.h"

/**
 * get_argv - get the arguments from line
 * @command: poiner to line
 * Return: return pointer to arg or NULL in error
 */
char **get_argv(char *command)
{
	char **argv;
	int i = 0;
	size_t len = 0;

	len = get_tokens_num(command);
	if (!len)
		return (NULL);
	argv = malloc(sizeof(char *) * (len + 1));
	argv[0] = _strtok(command, " ");
	while (argv[i])
	{
		i++;
		argv[i] = _strtok(NULL, " ");
	}

	return (argv);
}

/**
* get_tokens_num - get number of tokens
* @command: command
* Return: number of tokens
*/
size_t get_tokens_num(char *command)
{
	int i = 0, num = 1;

	if (!command || !*command)
		return (0);

	while (command[i])
	{
		if (command[i] == ' ')
		{
			while (command[i] == ' ')
				i++;
			if (command[i] == '\n')
				break;
			if (command[i])
				num++;
			continue;
		}
		i++;
	}
	return (num);
}

