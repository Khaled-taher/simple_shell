#include "main.h"
/**
 * skip - moves the pointer of chars to skip some chars
 * @str: the array or chars of the pointer
 * @to_skip: set of chars to skip
 * Return: the number of characters that the pointer skipped
 */
int skip(char *str, const char *to_skip)
{
	int count = 0;
	int i, j = 0;
	int found = 0;
	int len = str_len(to_skip);

	while (1)
	{
		for (int i = 0; i < len; i++)
		{
			if (str[j] == to_skip[i])
			{
				count++;
				break;
			}
			else if (i == len - 1)
			{
				found = 1;
				break;
			}
		}
	if (found)
	return (count);
	j++;
	}
}
