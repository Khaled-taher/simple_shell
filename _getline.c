#include "main.h"

/**
 * _getline - works similar to getline
 * @string: pointer to strings that stores the input line
 * @size: the size of the string
 * @stream: indicates the input stream
 * Return: the number of characters that are read
 */
ssize_t _getline(char **string, size_t *size, FILE *stream)
{int count = 0;
int result;
char c;
char *new_ptr;
	if (*string == NULL || *size == 0)
	{*size = 64;
	*string = (char *)malloc(*size);
			if (*string == NULL)
			{
				return (-1);
			}
	}
	while ((result = read(fileno(stream), &c, 1)) == 1)
	{
		if (count >= (int)(*size - 1))
		{
			*size *= 2;

			new_ptr = (char *)realloc(*string, *size);

			if (new_ptr == NULL)
			{free(*string);
			return (-1);
			}
		*string = new_ptr;
		}

		*(*string + count++) = c;
		if (c == '\n')
		{
			break;
		}
	}

	if (count == 0 && result == 0)
		return (0);
	else if (result == -1)
		return (-1);
*(*string + count) = '\0';
return ((ssize_t)(count));
}
