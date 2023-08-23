#include "main.h"

/**
 * get_command - get the commands and their arguments from line
 * @lineptr: poiner to line
 * Return: return pointer to commands or NULL in error
 */
char **get_command(char *lineptr)
{
	char **command = NULL, *token;
	int i = 0, error = 0, command_num = 1;

	get_command_helper(lineptr, &command_num, &error);

	if (error == 1)
	{
		helper_error(command);
		return (command);
	}

	command = malloc(sizeof(char *) * (command_num + 1));
	if (command == NULL)
	{
		perror("Error:");
		helper_error(command);
		return (command);
	}
	token = _strtok(lineptr, "#;\n");
	while (token != NULL && i < command_num)
	{
		command[i] = strdup(token);
		token = _strtok(NULL, " \n");
		i++;
	}
	command[i] = NULL;
	return (command);
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
			if (get_command_helper2(lineptr, error, i) == -1)
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
 * @error: flag to determine the occurance of erre
 * @i: current index
 * Return: 0 if no break and -1 if break
 */
int get_command_helper2(char *lineptr, int *error, int i)
{
	if (lineptr[i + 1] == '#')
		return (-1);
	return (0);
}
/**
 * helper_error - to change variable when error occurs
 * @command: poiner to commands
 * Return: nothing
 */
void helper_error(char **command)
{
	command = malloc(sizeof(char *) * 2);
	command[0] = strdup(" ");
	command[1] = NULL;
}
