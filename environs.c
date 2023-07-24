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

	for (index0 = 0; environs[index0]; index0++)
		free(environs[index0]);
	free(environs);
}

/**
 * _copyenv - this creates a copy of the environment
 * Return: NULL if an error occurs, O/w - a double pointer to the new copy
 */

char **_copyenv(void)
{
	char **new_environs;
	size_t size;
	int index0;

	for (size = 0; environs[size]; size++)
		;

	new_environs = malloc(sizeof(char *) * (size + 1));
	if (!new_environs)
		return (NULL);

	for (index0 = 0; environs[index0]; index0++)
	{
		new_environs[index0] = malloc(_strlen(environs[index0]) + 1);

		if (!new_environs[index0])
		{
			for (index0--; index0 >= 0; index0--)
				free(new_environs[index0]);
			free(new_environs);
			return (NULL);
		}
		_strcpy(new_environs[index0], environs[index0]);
	}
	new_environs[index0] = NULL;

	return (new_environs);
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
	for (index0 = 0; environs[index0]; index0++)
	{
		if (_strncmp(var, environs[index0], length) == 0)
			return (&environs[index0]);
	}

	return (NULL);
}
