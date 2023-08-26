#include "main.h"
/**
* concat - string concat
* @dest: dest (self change - pass by reference)
* @src: src
* Return: A pointer to dest
*/
char *concat(char **dest, char *src)
{
	char *temp = NULL;
	size_t i = 0, len = 0, len2 = 0, len3 = 0;

	len = _strlen(*dest);
	len2 = _strlen(src);
	len3 = len + len2;
	temp = malloc(sizeof(char) * (len3 + 1));
	if (!temp)
		return (NULL);
	while (len3)
	{
		if (i < len)
			temp[i] = (*dest)[i];
		else
			temp[i] = src[i - len];
		++i;
		--len3;
	}
	temp[i] = '\0';
	free(*dest);
	*dest = temp;
	return (temp);
}

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
