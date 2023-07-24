#include "main.h"

char *error_124(char **arg);
char *error_125(char **arg);

/**
 * error_124 - this creates an error message for command not found failures
 * @arg: an array of arguments passed to the command
 * Return: the error string
 */


char *error_124(char **arg)
{
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	length = _strlen(name) + _strlen(hist_str) + _strlen(arg[0]) + 16;
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
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}

/**
 * error_125 - this creates an error message for permission denied failures
 * @arg: an array of arguments passed to the command
 * Return: the error string
 */

char *error_125(char **arg)
{
	char *error, *hist_str;
	int length;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

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
	_strcat(error, ": ");
	_strcat(error, arg[0]);
	_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}
