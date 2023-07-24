#include "main.h"


char *error_env00(char **arg);
char *error_01(char **arg);
char *error_02_exit(char **arg);
char *error_02_cd(char **arg);
char *error_02_syntax(char **arg);


/**
 * error_env00 - this creates an error message for shellof_env errors
 * @arg: an array of arguments passed to the command
 * Return: the error string
 */

char *error_env00(char **arg)
{
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	arg--;
	length = _strlen(name) + _strlen(hist_str) + _strlen(arg[0]) + 45;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, arg[0]);
	_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * error_01 - this creates an error message for shellof_alias errors
 * @arg: an array of arguments passed to the command
 * Return: the error string
 */

char *error_01(char **arg)
{
	char *error;
	int length;

	length = _strlen(name) + _strlen(arg[0]) + 13;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, arg[0]);
	_strcat(error, " not found\n");

	return (error);
}


/**
 * error_02_exit - this creates an error message for shellof_exit errors
 * @arg: an array of arguments passed to the command
 * Return: the error string
 */

char *error_02_exit(char **arg)
{
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	length = _strlen(name) + _strlen(hist_str) + _strlen(arg[0]) + 27;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": exit: Invalid number: ");
	_strcat(error, arg[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_02_cd - this creates an error message for shellof_cd errors
 * @arg: an array of arguments passed to the command
 * Return: the error string
 */

char *error_02_cd(char **arg)
{
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	if (arg[0][0] == '-')
		arg[0][2] = '\0';
	length = _strlen(name) + _strlen(hist_str) + _strlen(arg[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	if (arg[0][0] == '-')
		_strcat(error, ": cd: Invalid option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, arg[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}


/**
 * error_02_syntax - this creates an error message for syntax errors
 * @arg: an array of arguments passed to the command
 * Return: the error string
 */

char *error_02_syntax(char **arg)
{
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	length = _strlen(name) + _strlen(hist_str) + _strlen(arg[0]) + 33;
	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, arg[0]);
	_strcat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
