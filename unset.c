#include "main.h"

/**
 * _unsetenv - to set value of new variable or modify it
 * @head: pointer to environment variables
 * @name: name of variable to set
 * Return: return 0 if sucessed and -1 in fail
 */
int _unsetenv(list_t *head, const char *name)
{
	char *str;
	int len, index = 0, i;
	list_t *current, *tmp, *tmp2;

	if (check_name(name) == -1)
		return (-1);
	len = _strlen(name);
	current = head;
	while (current)
	{
		str = _strndup(current->str, len);
		if (_strcmp(name, str) == 0 && current->str[len] == '=')
			break;
		current = current->next;
		index++;
	}
	if (current == NULL)
	{
		return (0);
	}
	else
	{
		if (index == 0)
		{
			tmp = head;
			head = head->next;
			free(tmp);
			return (0);
		}
		tmp = head;
		for (i = 0; i < index - 1; i++)
			tmp = tmp->next;
		tmp2 = tmp->next;
		tmp->next = tmp2->next;
		free(tmp2);
		return (0);
	}
}
