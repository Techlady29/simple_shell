#include "main.h"


void free_env(void);
char **_copyenv(void);
char **_getenv(const char *var);

/**
 * free_env - this frees the the environment copy
 */

void free_env(void)
{
	int index0;

	for (index0 = 0; environ[index0]; index0++)
		free(environ[index0]);
	free(environ);
}

/**
 * _copyenv - this creates a copy of the environment
 * Return: NULL if an error occurs, O/w - a double pointer to the new copy
 */

char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int index0;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index0 = 0; environ[index0]; index0++)
	{
		new_environ[index0] = malloc(_strlen(environ[index0]) + 1);

		if (!new_environ[index0])
		{
			for (index0--; index0 >= 0; index0--)
				free(new_environ[index0]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[index0], environ[index0]);
	}
	new_environ[index0] = NULL;

	return (new_environ);
}


/**
 * _getenv - this gets an environmental variable from the PATH
 * @var: the name of the environmental variable to get
 * Return: NULL if the environmental variable does not exist, otherwise - a
 * pointer to the environmental variable
 */

char **_getenv(const char *var)
{
	int index0, length;

	length = _strlen(var);
	for (index0 = 0; environ[index0]; index0++)
	{
		if (_strncmp(var, environ[index0], length) == 0)
			return (&environ[index0]);
	}

	return (NULL);
}
