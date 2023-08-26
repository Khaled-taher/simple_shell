#include "main.h"

/**
 * _setenv - to set value of new variable or modify it
 * @head: pointer to environment variables
 * @name: name of variable to set
 * @value: value to be set
 * @overwrite: if not 0 then overwrite old value
 * Return: return 0 if sucessed and -1 in fail
 */
int _setenv(list_t *head, const char *name,
		const char *value, int overwrite)
{
	char *str;
	int name_len;
	list_t *current = NULL;

	if (check_name(name) == -1)
	{
		errno = EINVAL;
		perror("Error:");
		return (-1);
	}
	name_len = strlen(name);
	current = head;
	while (current)
	{
		str = strndup(current->str, name_len);
		if (strcmp(name, str) == 0 && current->str[name_len] == '=')
			break;
		current = current->next;
	}
	if (current == NULL)
	{
		return (_setenv_helper1(head, name, value));
	}
	else
	{
		if (overwrite != 0)
		{
			return (_setenv_helper2(current, name, value));
		}
		return (0);
	}
	return (-1);
}

/**
 * _setenv_helper1 - to set value of new variable or modify it
 * @head: pointer to environment variables
 * @name: name of variable to set
 * @value: value to be set
 * Return: return 0 if sucessed and -1 in fail
 */
int _setenv_helper1(list_t *head, const char *name, const char *value)
{
	list_t *new, *last;
	int i = 0, name_len, val_len;

	name_len = strlen(name);
	val_len = strlen(value);
	new = malloc(sizeof(list_t));
	if (new == NULL)
	{
		perror("Error:");
		return (-1);
	}
	new->str = malloc(sizeof(char) * (name_len + val_len + 2));
	if (new->str == NULL)
	{
		perror("Error:");
		return (-1);
	}
	for (i = 0; i < name_len; i++)
		new->str[i] = name[i];
	new->str[i] = '=';
	for (i = name_len + 1; i < (name_len + val_len + 1); i++)
		new->str[i] = value[i - name_len - 1];
	new->str[i] = '\0';
	new->next = NULL;
	last = head;
	while (last->next)
		last = last->next;
	last->next = new;
	return (0);
}

/**
 * _setenv_helper2 - to set value of new variable or modify it
 * @current: pointer to environment variables
 * @name: name of variable to set
 * @value: value to be set
 * Return: return 0 if sucessed and -1 in fail
 */
int _setenv_helper2(list_t *current, const char *name, const char *value)
{
	int i, name_len, val_len;

	name_len = strlen(name);
	val_len = strlen(value);
	free(current->str);
	current->str = NULL;
	current->str = malloc(sizeof(char) * (name_len + val_len + 2));
	if (current->str == NULL)
	{
		perror("Error:");
		return (-1);
	}
	for (i = 0; i < name_len; i++)
		current->str[i] = name[i];
	current->str[i] = '=';
	for (i = name_len + 1; i < (name_len + val_len + 1); i++)
		current->str[i] = value[i - name_len - 1];
	current->str[i] = '\0';
	return (0);
}

/**
 * check_name - to check if name contain '='
 * @name: name of variable to set
 * Return: return 0 if sucessed and -1 in fail
 */
int check_name(const char *name)
{
	int i = 0;

	while (name[i] != '\0')
	{
		if (name[i] == '=')
			return (-1);
		i++;
	}
	return (0);
}
