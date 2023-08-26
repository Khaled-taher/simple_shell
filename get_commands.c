#include "main.h"

void after_spaces(char *str, int *i)
{
	while (str[*i] == ' ')
		++*i;
}

int init_commands(char ***commands, char *lineptr)
{
	int start = 0, final = 0, commands_num = 1, error = 0;

	after_spaces(lineptr, &start);
	final = start;
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
 * get_command - get the commands and their arguments from line
 * @lineptr: poiner to line
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

/**
 * get_command_helper - count numbers of commands and print error messages
 * @lineptr: pointer to line in the line
 * @command_num: number of commands
 * @error: flag to determine the occurance of error
 * Return: nothing
 */
void get_command_helper(char *lineptr, int *command_num, int *error)
{
	int i = 0;

	while (lineptr[i] != '\0')
	{
		if (lineptr[0] == '#')
		{
			(*error) = 1;
			break;
		}
		if (lineptr[i] == ' ')
			if (get_command_helper2(lineptr, i) == -1)
				break;
		if (lineptr[i] == ';' && lineptr[i + 1] != '\0')
		{
			if (lineptr[i + 1] == ';')
			{
				printf("bash: syntax error near unexpected token `;`\n");
				(*error) = 1;
				break;
			}
			else
			{
				while (lineptr[i + 1] == ' ')
				{
					if (lineptr[i + 2] == ';')
					{
						printf("bash: syntax error near unexpected token `;`\n");
						(*error) = 1;
						break;
					}
					i++;
				}
				if (lineptr[i + 1] == '#')
					break;
				(*command_num)++;
			}
		}
		i++;
	}
}

/**
 * get_command_helper2 - count numbers of commands and print error messages
 * @lineptr: pointer to line in the line
 * @i: current index
 * Return: 0 if no break and -1 if break
 */
int get_command_helper2(char *lineptr, int i)
{
	if (lineptr[i + 1] == '#')
		return (-1);
	return (0);
}
/**
 * helper_error - to change variable when error occurs
 * @command: pointer to commands
 * Return: nothing
 */
void helper_error(char **command)
{
	command = malloc(sizeof(char *) * 2);
	command[0] = strdup(" ");
	command[1] = NULL;
}
