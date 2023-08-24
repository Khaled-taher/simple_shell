#include "main.h"
/**
 * findpos - Finds the position of the first character from a set of characters
 * @str: the string to search in
 * @to_find: set of characters to search for
 * Return: The index of the first char or zero if not found
 */
int findpos(char *str, const char *to_find)
{
int i, count = 0;
int len = str_len(to_find);
	while (*str)
	{
		for (i = 0; i < len; i++)
		{
			if (str[count] == to_find[i] || str[count] == '\0')
			{
				return (count);
			}
		}
	count++;
	}
return (0);
}
