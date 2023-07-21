#include "main.h"

void free_mem(char **arg, char **p);
char *get_pid(void);
char *make_env_value(char *b, int l);
void handle_variable(char **arg, int *ret_com);

/**
 * free_mem - A program that frees the memory from that arguments
 * @arg: A double pointer of command arguments
 * @p: A pointer to pointer at the start of the arguments
 */
void free_mem(char **arg, char **p)
{
	size_t j;

	for (j = 0; arg[j] || arg[j + 1]; j++)
		free(arg[j]);

	free(p);
}
/**
 * get_pid - A program that generates the current ID
 * Return: Current ID otherwise NULL if there is a failure
 */
char *get_pid(void)
{
	size_t j = 0;
	char *b;
	ssize_t f;

	f = open("/proc/self/stat", O_RDONLY);
	if (f == -1)
	{
		perror("Cannot read file");
		return (NULL);
	}
	b = malloc(120);
	if (!b)
	{
		close(f);
		return (NULL);
	}
	read(f, b, 120);
	while (b[j] != ' ')
		j++;
	b[j] = '\0';

	close(f);
	return (b);
}

/**
 * make_env_value - A program that generates the value interelates
 *                  to the env variable
 * @b: The env variable to be used
 * @l: This is the lenght of the env variable
 *
 * Return: An empty string if value is not found
 *         else print value of en variable
 */
char *make_env_value(char *b, int l)
{
	char **v_add;
	char *r = NULL, *t, *v;

	v = malloc(l + 1);
	if (!v)
		return (NULL);
	v[0] = '\0';
	_strncat(v, b, l);

	v_add = _getenv(v);
	free(v);
	if (v_add)
	{
		t = *v_add;
		while (*t != '=')
			t++;
		t++;
		r = malloc(_strlen(t) + 1);
		if (r)
			_strcpy(r, t);
	}

	return (r);
}

/**
 * handle_variable - A program that handles the variable replacement
 * @arg: A double pointer of command arguments
 * @ret_com: A pointer to a pointer at the start of the arguments
 */
void handle_variable(char **arg, int *ret_com)
{
	int p, q = 0, l;
	char *r = NULL, *line = NULL, *n_line;

	line = *arg;
	for (p = 0; line[p]; p++)
	{
		if (line[p] == '$' && line[p + 1] && line[p + 1] != ' ')
		{
			if (line[p + 1] == '$')
			{
				r = get_pid();
				q = p + 2;
			}
			else if (line[p + 1] == '?')
			{
				r = _itoa(*ret_com);
				q = p + 2;
			}
			else if (line[p + 1])
			{
				for (q = p + 1; line[q] &&
						line[q] != '$' &&
						line[q] != ' '; q++)
					;

				l = q - (p + 1);
				r = make_env_value(&line[p + 1], l);
			}
			n_line = malloc(p + _strlen(r)
					  + _strlen(&line[q]) + 1);
			if (!arg)
				return;
			n_line[0] = '\0';
			_strncat(n_line, line, p);
			if (r)
			{
				_strcat(n_line, r);
				free(r);
				r = NULL;
			}
			_strcat(n_line, &line[q]);
			free(line);
			*arg = n_line;
			line = n_line;
			p = -1;
		}
	}
}
