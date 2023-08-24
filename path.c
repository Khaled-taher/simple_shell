#include "main.h"

/**
 * build_path - build linked list of paths
 * @path: pointer pointed to path varaible
 * Return: pointer to first node of path
 */
list_t *build_path(char *path)
{
	list_t *head = NULL;
	char *token;
	list_t *new, *last;

	token = strtok(path, ":");
	while (token != NULL)
	{
		new = malloc(sizeof(list_t));
		if (new == NULL)
		{
			printf("Error!!");
		}
		new->str = _strdup(token);
		new->next = NULL;
		if (head == NULL)
		{
			head = new;
		}
		else
		{
			last = head;
			while (last->next)
				last = last->next;
			last->next = new;
		}
		token = strtok(NULL, ":");
	}
	return (head);
}

/**
 * check_path - check if comamnd in path
 * @env: pointer pointed to enviroment
 * @argv: pointer pointed to argument
 * @status: status of operation
 * Return: pointer 0 if success and -1 in fail and 98 if not found
 */
char **check_path(list_t *env, char **argv, int *status)
{
	int len = 0, i;
	char *command, **new_argv;
	list_t *path;
	struct stat st;

	if (stat(argv[0], &st) == 0)
	{
		(*status) = 0;
		return (argv);
	}
	while (argv[len] != NULL)
		len++;
	path = build_path(_getenv(env, "PATH"));
	while (path)
	{
		command = check_path_helper(path, argv[0], status);
		if (stat(command, &st) == 0)
		{
			new_argv = malloc(sizeof(char *) * (len + 1));
			if (new_argv == NULL)
			{
				(*status) = -1;
				free(command);
				return (argv);
			}
			new_argv[0] = _strdup(command);
			free(command);
			for (i = 1; i < len; i++)
				new_argv[i] = argv[i];
			_free_environ(path);
			(*status) = 0;
			return (new_argv);
		}
		path = path->next;
	}
	_free_environ(path);
	(*status) = 98;
	return (argv);
}

/**
 * check_path_helper - check if comamnd in path
 * @path: pointer pointed to enviroment
 * @argv: pointer pointed to argument
 * @status: status of operation
 * Return: pointer 0 if success and -1 in fail and 98 if not found
 */
char *check_path_helper(list_t *path, char *argv, int *status)
{
	int len_str, len_argv0, i = 0;
	char *command;

	len_str = _strlen(path->str);
	len_argv0 = _strlen(argv);

	command = malloc(sizeof(char) * (len_str + len_argv0 + 2));
	if (command == NULL)
	{
		(*status) = -1;
		return (NULL);
	}
	for (i = 0; i < len_str; i++)
		command[i] = path->str[i];
	command[i] = '/';
	i++;
	for (i = len_str + 1; i < len_str + len_argv0 + 1; i++)
		command[i] = argv[i - len_str - 1];
	command[i] = '\0';
	return (command);
}

/**
 * _getenv - get value associated with variable named
 * @head: pointer to environment variables
 * @name: name of varaible
 * Return: return pointer pointed to value of name
 */
char *_getenv(list_t *head, char *name)
{
	int len, i = 0;
	char *value = NULL;
	list_t *current = NULL;

	len = _strlen(name);
	current = head;
	while (current)
	{
		value = strndup(current->str, len);
		if (strcmp(name, value) == 0 && current->str[len] == '=')
			break;
		current = current->next;
	}
	free(value);
	i = len + 1;
	while (current->str[i] != '\0')
	{
		i++;
	}
	i = i - len;
	value = malloc(sizeof(char) * i);
	if (value == NULL)
	{
		printf("Error:");
		return (NULL);
	}
	i = len + 1;
	while (current->str[i] != '\0')
	{
		value[i - len - 1] = current->str[i];
		i++;
	}
	value[i - len - 1] = '\0';
	return (value);
}
