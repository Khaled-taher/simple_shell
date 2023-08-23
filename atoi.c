#include "main.h"

/**
 * _atoi - change n to 98
 * @s: pointer to string
 * Return: return nothing
 */
int _atoi(char *s)
{
	int  i, min, is;
	unsigned int num;

	i = 0;
	num = 0;
	is = 0;
	min = 0;

	while (s[i])
	{
		while (s[i] >= '0' && s[i] <= '9')
		{
			num = (num * 10) + (s[i] - '0');
			is = 1;
			i = i + 1;
		}
		if (s[i] == '-')
			min = min + 1;
		if (is == 1)
			break;
		i = i + 1;

	}
	if (min % 2 == 1)
		num = -num;
	return (num);
}
