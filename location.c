#include "main.h"

char *fill_path(char *p);
list_t *get_path(char *p);

/**
 * get_location - A program that locates he command
 * @com: The pointer to be used
 * Return: NULL if an error occurs
 */
char *get_location(char *com)
{
	char **p, *t;
	list_t *dir, *h;
	struct stat st;

	p = _getenv("PATH");
	if (!p || !(*p))
		return (NULL);

	dir = get_path(*p + 5);
	h = dir;

	while (dir)
	{
		t = malloc(_strlen(dir->d) + _strlen(com) + 2);
		if (!t)
			return (NULL);

		_strcpy(t, dir->d);
		_strcat(t, "/");
		_strcat(t, com);

		if (stat(t, &st) == 0)
		{
			free_list(h);
			return (t);
		}

		dir = dir->next;
		free(t);
	}

	free_list(h);

	return (NULL);
}
/**
 * fill_path - A program that jsut fills up the path
 * @p: The path to be used
 * Return: The copy of the path
 */
char *fill_path(char *p)
{
	int k, l = 0;
	char *copy, *print;

	print = *(_getenv("PWD")) + 4;
	for (k = 0; p[k]; k++)
	{
		if (p[k] == ':')
		{
			if (p[k + 1] == ':' || k == 0 || p[k + 1] == '\0')
				l += _strlen(print) + 1;
			else
				l++;
		}
		else
			l++;
	}
	copy = malloc(sizeof(char) * (l + 1));
	if (!copy)
		return (NULL);
	copy[0] = '\0';
	for (k = 0; p[k]; k++)
	{
		if (p[k] == ':')
		{
			if (k == 0)
			{
				_strcat(copy, print);
				_strcat(copy, ":");
			}
			else if (p[k + 1] == ':' || p[k + 1] == '\0')
			{
				_strcat(copy, ":");
				_strcat(copy, print);
			}
			else
				_strcat(copy, ":");
		}
		else
		{
			_strncat(copy, &p[k], 1);
		}
	}
	return (copy);
}

/**
 * get_path - A program the parses a  list of directories into a linked list
 * @p: The path to be used
 * Return: A pointer to the list
 */
list_t *get_path(char *p)
{
	int i;
	char **dir, *copy;
	list_t *h = NULL;

	copy = fill_path(p);
	if (!copy)
		return (NULL);
	dir = _strtok(copy, ":");
	free(copy);
	if (!dir)
		return (NULL);

	for (i = 0; dir[i]; i++)
	{
		if (add_node_end(&h, dir[i]) == NULL)
		{
			free_list(h);
			free(dir);
			return (NULL);
		}
	}

	free(dir);

	return (h);
}
