#include "main.h"

void _unsetenv(void);
void _env(void);
void help_record(void);
void _setenv(void);

/**
 * _unsetenv - this displays information on the shellof builtin command
 *             unsetenv
 */

void _unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environmental variable.\n\n\tIf it fails, prints a ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}


/**
 * _env - this displays information on the shellof builtin command env
 */

void _env(void)
{
	char *msg = "env: env\n\tThis prints the current environment.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * _setenv - this displays information on the shellof builtin
 * command setenv
 */

void _setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tThis initializes a new";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tIf it fails, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
