#include "main.h"

/**
* after_spaces - after spaces
* @str: str
* @i:i
*/
void after_spaces(char *str, int *i)
{
	while (str[*i] == ' ')
		++*i;
}

/**
* init_commands - init commands
* @commands: commands
* @lineptr: line pointer
* Return: int
*/
int init_commands(char ***commands, char *lineptr)
{
	int start = 0, final = 0, commands_num = 1, error = 0;

	after_spaces(lineptr, &start);
	final = start;
	if (start == _strlen(lineptr) - 1)
		return (1);
	while (!error && lineptr[final])
	{
		if (lineptr[final] == ';' || lineptr[final] == '|' ||
			lineptr[final] == '&' ||
			(final && lineptr[final] == '#' && lineptr[final - 1] == ' '))
		{
			if (final && lineptr[final - 1] == ' ' && lineptr[final] == '#')
			{
				commands_num++;
				break;
			}
			if (lineptr[final + 1] != '&' && lineptr[final] == '&')
				error = 1;
			if (lineptr[final + 1] != '|' && lineptr[final] == '|')
				error = 1;
			if (lineptr[final] == '&' || lineptr[final] == '|')
				final++;
			commands_num++;
			after_spaces(lineptr, &final);
			start = final;
		}
		final++;
	}
	if (error)
	{
		write(STDERR_FILENO, "ERROR", 5);
		return (1);
	}
	*commands = malloc(sizeof(char *) * (commands_num + 1));
	return (0);
}

/**
* get_commands - get the commands and their arguments from line
* @lineptr: pointer to line
* Return: return pointer to commands or NULL in error
*/
char **get_commands(char *lineptr)
{
	char **commands = NULL;
	int i = 0, start = 0, final = 0;

	fflush(stdout);
	if (init_commands(&commands, lineptr))
		return (NULL);
	after_spaces(lineptr, &start);
	final = start;
	while (1)
	{
		if (lineptr[final] == ';' || lineptr[final] == '|' ||
			lineptr[final] == '&' ||
			(final && lineptr[final] == '#' && lineptr[final - 1] == ' ') ||
			!lineptr[final])
		{
			if (final && lineptr[final - 1] == ' ' && lineptr[final] == '#')
			{
				commands[i++] = _strndup(&lineptr[start], final - start);
				break;
			}
			commands[i++] = _strndup(&lineptr[start], final - start);
			if (!lineptr[final])
				break;
			if (lineptr[final] == '&' || lineptr[final] == '|')
				final++;
			final++;
			after_spaces(lineptr, &final);
			start = final;
			continue;
		}
		final++;
	}
	commands[i] = NULL;
	commands[i - 1][_strlen(commands[i - 1]) - 1] = '\0';
	return (commands);
}

