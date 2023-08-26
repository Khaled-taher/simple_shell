#include "main.h"
/**
* unsigned_to_str - ui 2 str
* @line_n: line number
* Return: string
*/
char *unsigned_to_str(int line_n)
{
	char *str = NULL;
	int tmp = 0, len = 0;

	if (!line_n)
		return (_strdup("0"));
	tmp = line_n;
	while (tmp)
	{
		tmp /= 10;
		len++;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	tmp = line_n;
	str[len] = '\0';
	while (tmp)
	{
		str[len - 1] = (tmp % 10) + '0';
		--len;
		tmp /= 10;
	}
	return (str);
}
/**
 * get_path - check if comamnd in path
 * @env: pointer pointed to enviroment
 * @argv: pointer pointed to argument
 * @status: status of operation
 * Return: pointer 0 if success and -1 in fail and 98 if not found
 */
char *get_path(list_t *env, char **argv, int *status)
{
	char *tmp = NULL, *path = NULL, *global_path = NULL;

	if (!argv || !argv[0] || !argv[0][0])
		return (NULL);
	if (argv[0][0] == '/')
		path = _strdup(argv[0]);
	else if (argv[0][0] == '.' && argv[0][1] == '/')
	{
		path = _getenv(env, "PWD");
		concat(&path, "/");
		concat(&path, &argv[0][2]);
	}
	else
	{
		global_path = _getenv(env, "PATH");
		tmp = _strtok(global_path, ":");
		while (tmp)
		{
			path = _strdup(tmp);
			concat(&path, "/");
			concat(&path, argv[0]);
			tmp = _strtok(NULL, ":");
			if (access(path, F_OK && X_OK) == -1)
			{
				if (!tmp)
					break;
				free(path);
			}
			else
				break;
		}
		free(global_path);
	}
	if (access(path, F_OK && X_OK) == -1)
	{
		*status = 127;
		free(path);
		return (NULL);
	}
	return (path);
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
		value = _strndup(current->str, len);
		if (!_strcmp(name, value) && current->str[len] == '=')
			break;
		free(value);
		value = NULL;
		current = current->next;
	}
	if (!value)
		return (NULL);
	free(value);

	i = len + 1;
	while (current->str[i] != '\0')
		i++;

	i = i - len;
	value = malloc(sizeof(char) * i);

	i = len + 1;
	while (current->str[i] != '\0')
	{
		value[i - len - 1] = current->str[i];
		i++;
	}
	value[i - len - 1] = '\0';
	return (value);
}
