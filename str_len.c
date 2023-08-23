#include "main.h"

/**
 * str_len - calculates the length of a string
 * @str: the string
 * Return: the number of chars in the string
 */
int str_len(const char *str)
{
	int len = 0;

	while (*str != '\0')
	{
		len++;
		str++;
	}
return (len);
}
