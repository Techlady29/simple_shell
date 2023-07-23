#include "main.h"

int shellof_geten(char **arg, char __attribute__((__unused__)) **p);
int shellof_ungeten(char **arg, char __attribute__((__unused__)) **p);
int shellof_en(char **arg, char __attribute__((__unused__)) **p);


/**
 * shellof_geten - this changes or adds an environmental variable to the PATH
 * @arg: an array of arguments passed to the shell
 * @p: a double pointer to the beginning of arguements
 * Return: -1 if an error occurs otherwise - 0
 */

int shellof_geten(char **arg, char __attribute__((__unused__)) **p)
{
	char **en_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!arg[0] || !arg[1])
		return (create_error(arg, -1));

	new_value = malloc(_strlen(arg[0]) + 1 + _strlen(arg[1]) + 1);
	if (!new_value)
		return (create_error(arg, -1));
	_strcpy(new_value, arg[0]);
	_strcat(new_value, "=");
	_strcat(new_value, arg[1]);

	en_var = _getenv(arg[0]);
	if (en_var)
	{
		free(*en_var);
		*en_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(arg, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * shellof_ungeten - this deletes an environmental variable from the PATH
 * @arg: an array of arguments passed to the shell
 * @p: a double pointer to the beginning of arguements
 * Return: -1 if an error occurs, otherwise - 0
 */

int shellof_ungeten(char **arg, char __attribute__((__unused__)) **p)
{
	char **en_var, **new_environ;
	size_t size;
	int index0, index1;

	if (!arg[0])
		return (create_error(arg, -1));
	en_var = _getenv(arg[0]);
	if (!en_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(arg, -1));

	for (index0 = 0, index1 = 0; environ[index0]; index0++)
	{
		if (*en_var == environ[index0])
		{
			free(*en_var);
			continue;
		}
		new_environ[index1] = environ[index0];
		index1++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}

/**
 * shellof_en - this prints the current environment
 * @arg: an array of arguments passed to the shell
 * @p: a double pointer to the beginning of arguements
 * Return: -1 if an error occurs otherwise - 0
 */


int shellof_en(char **arg, char __attribute__((__unused__)) **p)
{
	int index0;
	char bc = '\n';

	if (!environ)
		return (-1);

	for (index0 = 0; environ[index0]; index0++)
	{
		write(STDOUT_FILENO, environ[index0], _strlen(environ[index0]));
		write(STDOUT_FILENO, &bc, 1);
	}

	(void)arg;
	return (0);
}
