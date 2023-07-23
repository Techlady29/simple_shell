#include "main.h"

void help_ungeten(void);
void help_en(void);
void help_record(void);
void help_geten(void);

/**
 * help_ungeten - this displays information on the shellof builtin command
 * 'ungeten'
 */

void help_ungeten(void)
{
	char *msg = "ungeten: ungeten [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environmental variable.\n\n\tIf it fails, prints a ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}


/**
 * help_en - this displays information on the shellof builtin command 'en'
 */

void help_en(void)
{
	char *msg = "en: en\n\tThis prints the current environment.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_geten - this displays information on the shellof builtin
 * command 'geten'
 */

void help_geten(void)
{
	char *msg = "geten: geten [VARIABLE] [VALUE]\n\tThis initializes a new";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tIf it fails, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
