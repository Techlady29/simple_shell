#include "main.h"

int token_length(char *s, char *d);
int count_token(char *s, char *d);
char **_strtok(char *l, char *d);

/**
 * token_length - A program that locates a token in a string
 * @s: string to be used
 * @delim: The charater to be used
 * Return: The token
 */
int token_length(char *s, char *d)
{
	int i = 0, l = 0;

	while (*(s + i) && *(s + i) != *d)
	{
		l++;
		i++;
	}

	return (l);
}

/**
 * count_token - A program that counts the number of words in a string
 * @str: string to be used
 * @delim: character to be used
 * Return: number of words in a string
 */
int count_token(char *s, char *d)
{
	int i, t = 0, l = 0;

	for (i = 0; *(s + i); i++)
		l++;

	for (i = 0; i < l; i++)
	{
		if (*(s + i) != *d)
		{
			t++;
			i += token_length(s + i, d);
		}
	}

	return (t);
}

/**
 * _strtok - A program that parses a string
 * @l: The string to be used
 * @d: character to be used
 * Return: A pointer to the words
 */
char **_strtok(char *l, char *d)
{
	char **p;
	int i = 0, t, q, e, f;

	t = count_token(l, d);
	if (t == 0)
		return (NULL);

	p = malloc(sizeof(char *) * (t + 2));
	if (!p)
		return (NULL);

	for (q = 0; q < t; q++)
	{
		while (l[i] == *d)
			i++;

		e = token_length(l + i, d);

		p[q] = malloc(sizeof(char) * (e + 1));
		if (!p[q])
		{
			for (i -= 1; i >= 0; i--)
				free(p[i]);
			free(p);
			return (NULL);
		}

		for (f = 0; f < e; f++)
		{
			p[q][f] = l[i];
			i++;
		}

		p[q][f] = '\0';
	}
	p[q] = NULL;
	p[q + 1] = NULL;

	return (p);
}
