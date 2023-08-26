#include "main.h"

/**
 * _print_environ - to get a copy of environment
 * @head: pointer to environment variables
 * Return: nothing
 */
void _print_environ(list_t *head)
{
	list_t *h = NULL;

	if (!head)
		return;
	h = head;
	while (h)
	{
		write(STDOUT_FILENO, h->str, _strlen(h->str));
		write(STDOUT_FILENO, "\n", 1);
		h = h->next;
	}
}

/**
 * _cpy_environ - to get a copy of environment
 * @environ: pointer to environment variables
 * Return: return pointer to dyn alloc environ
 */
list_t *_cpy_environ(char **environ)
{
	list_t *head = NULL;
	int i = 0;
	list_t *new, *last;

	while (environ[i] != NULL)
	{
		new = malloc(sizeof(list_t));
		if (!new)
		{
			_free_environ(head);
			head = NULL;
			write(STDERR_FILENO, "Error:\n", 7);
			break;
		}
		new->str = _strdup(environ[i]);
		new->next = NULL;
		if (!head)
			head = new;
		else
		{
			last = head;
			while (last->next)
				last = last->next;
			last->next = new;
		}
		i++;
	}
	return (head);
}

/**
 * _free_environ - to set value of new variable or modify it
 * @head: pointer to environment variables
 *
 * Return: nothing
 */
void _free_environ(list_t *head)
{
	list_t *tmp;

	if (!head)
		return;

	while (head)
	{
		tmp = head;
		free(head->str);
		head = head->next;
		free(tmp);
	}
}

/**
 * list_to_arr - to convert list to array
 * @head: pointer to list of environment
 * Return: nothing
 */
char **list_to_arr(list_t *head)
{
	char **env;
	int len = 0, i;
	list_t *current;

	if (!head)
		return (NULL);
	current = head;
	while (current)
	{
		current = current->next;
		len++;
	}
	len++;
	env = malloc(sizeof(char *) * len);
	if (env == NULL)
	{
		perror("Error");
		return (NULL);
	}
	current = head;
	for (i = 0; i < len - 1; i++)
	{
		env[i] = _strdup(current->str);
		current = current->next;
	}
	env[i] = NULL;
	return (env);
}
