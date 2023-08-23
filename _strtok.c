#include "main.h"
/**
 * _strtok - split a string into tokens
 * @str: stirng to be tokenized
 * @delim: the delimiters
 * Return: a pointer on the first char of the token
 */
char *_strtok(char *str, const char *delim)
{
	static char *last_token;
	char *end;

	if (str != NULL)
	{
		last_token = str;
	}
	else
	{
		if (last_token == NULL)
			return (NULL);
		str = last_token;
	}
	str += skip(str, delim);
	if (*str == '\0')
	{
		last_token = NULL;
		return (NULL);
	}
	else
		end = str + findpos(str, delim);
	if (*end == '\0')
	{
		last_token = NULL;
	}
	else
	{
		*end = '\0';
		last_token = end + 1;
	}
return (str);
}
