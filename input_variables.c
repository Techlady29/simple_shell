#include "main.h"

char *get_arg(char *l, int *ret_com);
int name_arg(char **arg, char **p, int *ret_com);
int execute_arg(char **arg, char **p, int *ret_com);
int handle_arg(int *ret_com);
int test_arg(char **arg);

/**
 * get_arg - A program that generates a command from standard input
 * @l: This is where the command will be stored
 * @ret_com: The value of the command previosuly executed
 *
 * Return: NULL if there is an error otherwise return command
 */
char *get_arg(char *l, int *ret_com)
{
	size_t g = 0;
	ssize_t r;
	char *p = "$ ";

	if (l)
		free(l);

	r = _getline(&l, &g, STDIN_FILENO);

	if (r == -1)
		return (NULL);
	if (r == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, p, 2);
		return (get_arg(l, ret_com));
	}

	l[r - 1] = '\0';
	handle_variable(&l, ret_com);
	split_line(&l, r);

	return (l);
}

/**
 * name_arg - A program that splits operators  and calls them
 * @arg: This is the argument in the program
 * @p: A pointer to pointer at the beginning of the program
 * @ret_com: This is the previous command value returned
 * Return: The prevoius executed value reutrned
 */
int name_arg(char **arg, char **p, int *ret_com)
{
	int r, i;

	if (!arg[0])
		return (*ret_com);
	for (i = 0; arg[i]; i++)
	{
		if (_strncmp(arg[i], "||", 2) == 0)
		{
			free(arg[i]);
			arg[i] = NULL;
			arg = replace_aliases(arg);
			r = execute_arg(arg, p, ret_com);
			if (*ret_com != 0)
			{
				arg = &arg[++i];
				i = 0;
			}
			else
			{
				for (i++; arg[i]; i++)
					free(arg[i]);
				return (r);
			}
		}
		else if (_strncmp(arg[i], "&&", 2) == 0)
		{
			free(arg[i]);
			arg[i] = NULL;
			arg = replace_aliases(arg);
			r = execute_arg(arg, p, ret_com);
			if (*ret_com == 0)
			{
				arg = &arg[++i];
				i = 0;
			}
			else
			{
				for (i++; arg[i]; i++)
					free(arg[i]);
				return (r);
			}
		}
	}
	arg = replace_aliases(arg);
	r = execute_arg(arg, p, ret_com);
	return (r);
}

/**
 * execute_arg - A program that executes a command
 * @arg: The argument in a program
 * @p: A pointer to pointer at the beginning of the program
 * @ret_com: This is the previous command value returned
 * Return: The prevoius executed value reutrned
 */
int execute_arg(char **arg, char **p, int *ret_com)
{
	int r, k;
	int (*builtin)(char **arg, char **p);

	builtin = get_builtin(arg[0]);

	if (builtin)
	{
		r = builtin(arg + 1, p);
		if (r != EXIT)
			*ret_com = r;
	}
	else
	{
		*ret_com = exe_command(arg, p);
		r = *ret_com;
	}

	hist++;

	for (k = 0; arg[k]; k++)
		free(arg[k]);

	return (r);
}

/**
 * handle_arg - A program that gets, name, and executes a command
 * @ret_com: This is the previous command value returned
 * Return: EOF is an end or file is read else return previously
 *         executed command
 */
int handle_arg(int *ret_com)
{
	int r = 0, i;
	char **arg, *l = NULL, **p;

	l = get_arg(l, ret_com);
	if (!l)
		return (END_OF_FILE);

	arg = _strtok(l, " ");
	free(l);
	if (!arg)
		return (r);
	if (test_arg(arg) != 0)
	{
		*ret_com = 2;
		free_mem(arg, arg);
		return (*ret_com);
	}
	p = arg;

	for (i = 0; arg[i]; i++)
	{
		if (_strncmp(arg[i], ";", 1) == 0)
		{
			free(arg[i]);
			arg[i] = NULL;
			r = name_arg(arg, p, ret_com);
			arg = &arg[++i];
			i = 0;
		}
	}
	if (arg)
		r = name_arg(arg, p, ret_com);

	free(p);
	return (r);
}

/**
 * test_arg - A program that is used for testing
 * @arg: The argument in a program
 * Return: true if a wildcard is not placed properly
 */
int test_arg(char **arg)
{
	size_t r;
	char *c, *n;

	for (r = 0; arg[r]; r++)
	{
		c = arg[r];
		if (c[0] == ';' || c[0] == '&' || c[0] == '|')
		{
			if (r == 0 || c[1] == ';')
				return (create_error(&arg[r], 2));
			n = arg[r + 1];
			if (n && (n[0] == ';' || n[0] == '&' || n[0] == '|'))
				return (create_error(&arg[r + 1], 2));
		}
	}
	return (0);
}
