#include "main.h"

void *_realloc(void *p, unsigned int size, unsigned int new_size);
void assign_line(char **line, size_t *m, char *b, size_t d);
ssize_t _getline(char **line, size_t *m, FILE *stream);

/**
 * _realloc - This program reallocates a memory using malloc and free
 * @p: The pointer to be used
 * @size: The bytes
 * @new_size: The bytes for the new memory
 * Return: p if size is equal to new otherwise pointer to memory
 */
void *_realloc(void *p, unsigned int size, unsigned int new_size)
{
	void *m;
	char *copy, *f;
	unsigned int i;

	if (new_size == size)
		return (p);

	if (p == NULL)
	{
		m = malloc(new_size);
		if (m == NULL)
			return (NULL);

		return (m);
	}

	if (new_size == 0 && p != NULL)
	{
		free(p);
		return (NULL);
	}

	copy = p;
	m = malloc(sizeof(*copy) * new_size);
	if (m == NULL)
	{
		free(p);
		return (NULL);
	}

	f = m;

	for (i = 0; i < size && i < new_size; i++)
		f[i] = *copy++;

	free(p);
	return (m);
}

/**
 * assign_line - A program that re-assigns the line for getline
 * @line: The character to be used
 * @m: The size of line
 * @b: The string to assign to line
 * @d: This is the size of buffer
 */
void assign_line(char **line, size_t *m, char *b, size_t d)
{
	if (*line == NULL)
	{
		if (d > 120)
			*m = d;
		else
			*m = 120;
		*line = b;
	}
	else if (*m < d)
	{
		if (d > 120)
			*m = d;
		else
			*m = 120;
		*line = b;
	}
	else
	{
		_strcpy(*line, b);
		free(b);
	}
}

/**
 * _getline - A program to write our own getline funciton
 * @line: The buffer to store the string
 * @m: The size of line
 * @stream: The stream to read from
 * Return: The number of bytes
 */
ssize_t _getline(char **line, size_t *m, FILE *stream)
{
	static ssize_t i;
	ssize_t ret;
	char d = 'x', *b;
	int r;

	if (i == 0)
		fflush(stream);
	else
		return (-1);
	i = 0;

	b = malloc(sizeof(char) * 120);
	if (!b)
		return (-1);

	while (d != '\n')
	{
		r = read(STDIN_FILENO, &d, 1);
		if (r == -1 || (r == 0 && i == 0))
		{
			free(b);
			return (-1);
		}
		if (r == 0 && i != 0)
		{
			i++;
			break;
		}

		if (i >= 120)
			b = _realloc(b, i, i + 1);

		b[i] = d;
		i++;
	}
	b[i] = '\0';

	assign_line(line, m, b, i);

	ret = i;
	if (r != 0)
		i = 0;
	return (ret);
}
