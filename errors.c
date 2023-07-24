#include "main.h"

char *_itoa(int num);
int create_error(char **arg, int err);
int num_length(int num);

/**
 * _itoa - this converts an integer to a string
 * @num: the integer
 * Return: the converted string
 */

char *_itoa(int num)
{
	char *buff;
	int length = num_length(num);
	unsigned int num1;

	buff = malloc(sizeof(char) * (length + 1));
	if (!buff)
		return (NULL);

	buff[length] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buff[0] = '-';
	}
	else
	{
		num1 = num;
	}

	length--;
	do {
		buff[length] = (num1 % 10) + '0';
		num1 /= 10;
		length--;
	} while (num1 > 0);

	return (buff);
}

/**
 * create_error - this writes a custom error message to stderr
 * @arg: an array of arguments
 * @err: the error value
 * Return: the error value
 */

int create_error(char **arg, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = error_env00(arg);
		break;
	case 1:
		error = error_01(arg);
		break;
	case 2:
		if (*(arg[0]) == 'e')
			error = error_02_exit(++arg);
		else if (arg[0][0] == ';' || arg[0][0] == '&' || arg[0][0] == '|')
			error = error_02_syntax(arg);
		else
			error = error_02_cd(arg);
		break;
	case 124:
		error = error_124(arg);
		break;
	case 125:
		error = error_125(arg);
		break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}

/**
 * num_length - this counts the digit length of a number
 * @num: the number to measure
 * Return: the digit length
 */

int num_length(int num)
{
	unsigned int num1;
	int length = 1;

	if (num < 0)
	{
		length++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		length++;
		num1 /= 10;
	}

	return (length);
}
