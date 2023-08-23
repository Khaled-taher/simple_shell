#include "main.h"

/**
 * _strlen - concatinate to strings
 * @s: scource taht will be concatinated
 * Return: pointer to destination
 */
int _strlen(const char *s)
{
	if (*s)
		return (1 + _strlen(s + 1));
	else
		return (0);
}

/**
 * _strdup - duplicate string into another
 * @str: destination to concatinate after
 * Return: pointer to destination
 */
char *_strdup(char *str)
{
	unsigned int i;
	unsigned int size = 0;
	char *str2;

	if (str == NULL)
		return (NULL);
	while (str[size])
		size++;
	str2 = malloc(sizeof(char) * (size + 1));
	if (str2 == NULL)
		return (NULL);
	for (i = 0; i < size; i++)
		str2[i] = str[i];
	str2[i] = '\0';
	return (str2);
}

#include "main.h"

/**
 * _strcmp - compare between to strings
 * @s1: pointer to string 1
 * @s2: pointer to string 2
 * Return: 0 if same and number of different char
 */
int _strcmp(const char *s1, char *s2)
{
	int i, j, k, l, result;

	j = strlen(s1);
	k = strlen(s2);
	if (j >= k)
		l = j;
	else
		l = k;
	for (i = 0; i < l; i++)
	{
		if (s1[i] == s2[i])
			result = 0;
		else
		{
			result = s1[i] - s2[i];
			break;
		}
	}
	return (result);
}

/**
 * _strndup - duplicate n char of string into another
 * @str: destination to concatinate after
 * @n: number of char to be duplicated
 * Return: pointer to destination
 */
char *_strndup(char *str, int n)
{
	int size = 0, i;
	char *str2;

	if (str == NULL)
		return (NULL);
	while (str[size])
		size++;
	if (size < n)
		n = size;
	str2 = malloc(sizeof(char) * (n + 1));
	if (str2 == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < n; i++)
		str2[i] = str[i];
	str2[i] = '\0';
	return (str2);
}
