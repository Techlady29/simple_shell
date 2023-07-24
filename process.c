#include "main.h"

int cannot_open(char *path);
int process_file(char *path, int *ret_com);

/**
 * cannot_open - A program that throws an error when a command
 *               doesn't exist
 * @path: The path to be used
 * Return: Error 127 which  cannot open
 */

int cannot_open(char *path)
{
	char *e, *str;
	int l;

	str = _itoa(hist);
	if (!str)
		return (127);

	l = _strlen(name) + _strlen(str) + _strlen(path) + 16;
	e = malloc(sizeof(char) * (l + 1));
	if (!e)
	{
		free(str);
		return (127);
	}

	_strcpy(e, name);
	_strcat(e, ": ");
	_strcat(e, str);
	_strcat(e, ": Cannot open ");
	_strcat(e, path);
	_strcat(e, "\n");

	free(str);
	write(STDERR_FILENO, e, l);
	free(e);
	return (127);
}

/**
 * process_file - A program that process a file with commands
 * @path: The path to be used
 * @ret_com: The value of the previous command
 * Return: Error 127 cannot open
 */
int process_file(char *path, int *ret_com)
{
	ssize_t f, l_read, j;
	unsigned int line = 0;
	unsigned int size = 120;
	char *l, **arg, **p;
	char b[120];
	int r;

	hist = 0;
	f = open(path, O_RDONLY);
	if (f == -1)
	{
		*ret_com = cannot_open(path);
		return (*ret_com);
	}
	l = malloc(sizeof(char) * size);
	if (!l)
		return (-1);
	do {
		l_read = read(f, b, 119);
		if (l_read == 0 && line == 0)
			return (*ret_com);
		b[l_read] = '\0';
		line += l_read;
		l = _realloc(l, size, line);
		_strcat(l, b);
		size = line;
	} while (l_read);
	for (j = 0; l[j] == '\n'; j++)
		l[j] = ' ';
	for (; j < line; j++)
	{
		if (l[j] == '\n')
		{
			l[j] = ';';
			for (j += 1; j < line && l[j] == '\n'; j++)
				l[j] = ' ';
		}
	}
	handle_variable(&l, ret_com);
	split_line(&l, size);
	arg = _strtok(l, " ");
	free(l);
	if (!arg)
		return (0);
	if (test_arg(arg) != 0)
	{
		*ret_com = 2;
		free_mem(arg, arg);
		return (*ret_com);
	}
	p = arg;

	for (j = 0; arg[j]; j++)
	{
		if (_strncmp(arg[j], ";", 1) == 0)
		{
			free(arg[j]);
			arg[j] = NULL;
			r = name_arg(arg, p, ret_com);
			arg = &arg[++j];
			j = 0;
		}
	}

	r = name_arg(arg, p, ret_com);

	free(p);
	return (r);
}
