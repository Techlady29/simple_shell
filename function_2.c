#include "main.h"

char *_strchr(char *string, char d);
int _strspn(char *string, char *accept);
int _strcmp(char *string1, char *string2);
int _strncmp(const char *string1, const char *string2, size_t m);

/**
 * _strchr - A program that locates character in a string
 * @string: The string to be used
 * @d: The character to be used
 * Return: NULL if character to be used is not found
 */
char *_strchr(char *string, char d)
{
	int i;

	for (i = 0; string[i]; i++)
	{
		if (string[i] == d)
			return (string + i);
	}

	return (NULL);
}

/**
 * _strspn - A program that generates the length of a substring
 * @string: The string to be used
 * @accept: The prefix to be used
 * Return: The number of bytes in the string
 */
int _strspn(char *string, char *accept)
{
	int b = 0;
	int i;

	while (*string)
	{
		for (i = 0; accept[i]; i++)
		{
			if (*string == accept[i])
			{
				b++;
				break;
			}
		}
		string++;
	}
	return (b);
}

/**
 * _strcmp - A proram that compares two strings
 * @string1: The string to be compared to string 2
 * @string2: The string to be compared to string 1
 * Return: Positive byte an negative byte
 */
int _strcmp(char *string1, char *string2)
{
	while (*string1 && *string2 && *string1 == *string2)
	{
		string1++;
		string2++;
	}

	if (*string1 != *string2)
		return (*string1 - *string2);

	return (0);
}

/**
 * _strncmp - A program that comapres two string
 * @string1: The string to be compared to string 1
 * @string2: The string to be compared to string 2
 * * @m: The bytes
 * Return: 0 if string 1 and string 2 are the same
 */
int _strncmp(const char *string1, const char *string2, size_t m)
{
	size_t j;

	for (j = 0; string1[j] && string2[j] && j < m; j++)
	{
		if (string1[j] > string2[j])
			return (string1[j] - string2[j]);
		else if (string1[j] < string2[j])
			return (string1[j] - string2[j]);
	}
	if (j == m)
		return (0);
	else
		return (-15);
}
