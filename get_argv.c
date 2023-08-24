#include "main.h"

/**
 * get_argv - get the arguments from line
 * @lineptr: poiner to line
 * Return: return pointer to arg or NULL in error
 */
char **get_argv(char *lineptr)
{
	char **argv, *token;
	int i = 0, arg_num = 1, char_num = 0;

	if (get_argv_helper(lineptr, &arg_num, &char_num) == -1)
		return (NULL);

	if (char_num == 0)
		return (NULL);
	i = 0;
	argv = malloc(sizeof(char *) * (arg_num + 1));
	if (argv == NULL)
	{
		perror("Error:");
		return (NULL);
	}
	token = strtok(lineptr, " \n");
	if (token == NULL)
		return (NULL);
	while (token != NULL && i < arg_num)
	{
		argv[i] = strdup(token);
		token = strtok(NULL, " \n");
		i++;
	}
	argv[i] = NULL;

	return (argv);
}

/**
 * get_argv_helper - get the arguments from line
 * @lineptr: poiner to line
 * @arg_num: number of argument
 * @char_num: number of chars
 * Return: return 0 if succeed and -1 if error
 */
int get_argv_helper(char *lineptr, int *arg_num, int *char_num)
{
	int i = 0;

	while (lineptr[i] != '\0')
	{
		if (i == 0 && lineptr[i] == '#')
			break;

		if (lineptr[i] != ' ')
			(*char_num)++;

		if (lineptr[i] == ' ' && lineptr[i + 1] != ' ')
		{
			if (lineptr[i + 1] == ';')
				break;
			if (lineptr[i + 1] == '#')
				break;
			if (lineptr[i + 1] != '\n')
				(*arg_num)++;
		}
		i++;
	}
	return (0);
}
