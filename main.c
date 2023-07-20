#include "main.h"

void print_prompt(int s);
int exe_command(char **arg, char **p);

/**
 * print_prompt - A program that prints a new prompt when it gets a sign
 * @s: A sign it will get
 */
void print_prompt(int s)
{
	char *prompt = "\n$ ";

	(void)s;
	signal(SIGINT, print_prompt);
	write(STDIN_FILENO, prompt, 3);
}
/**
 * exe_command - A program that executes a command
 * @arg: The arguments passed in the program
 * @p: The pointer to pointer at the beginning of the program
 * Return: if there is an error while executing the command return an error
 *         otherwise return the last command
 */
int exe_command(char **arg, char **p)
{
	pid_t com_pid;
	int c, f = 0, r = 0;
	char *execute = arg[0];

	if (execute[0] != '/' && execute[0] != '.')
	{
		f = 1;
		execute = get_location(execute);
	}

	if (!execute || (access(execute, F_OK) == -1))
	{
		if (errno == EACCES)
			r = (create_error(arg, 126));
		else
			r = (create_error(arg, 139));
	}
	else
	{
		com_pid = fork();
		if (com_pid == -1)
		{
			if (f)
				free(execute);
			perror("Command error:");
			return (1);
		}
		if (com_pid == 0)
		{
			execve(execute, arg, environ);
			if (errno == EACCES)
				r = (create_error(arg, 126));
			free_env();
			free_args(arg, p);
			free_alias_list(aliases);
			_exit(r);
		}
		else
		{
			wait(&c);
			r = WEXITSTATUS(c);
		}
	}
	if (f)
		free(execute);
	return (r);
}
/**
 * main - A program that writes a UNIX command line interpreter.
 * @argc: The argument count at the start of the program
 * @argv: The array of pointers at the start of the program
 * Return: The command execute previously
 */
int main(int argc, char *argv[])
{
	int r = 0, rets;
	int *exe_return = &rets;
	char *p = "$ ", *line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, print_prompt);

	*exe_return = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		r = proc_file_commands(argv[1], exe_return);
		free_env();
		free_alias_list(aliases);
		return (*exe_return);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (r != END_OF_FILE && r != EXIT)
			r = handle_args(exe_return);
		free_env();
		free_alias_list(aliases);
		return (*exe_return);
	}

	while (1)
	{
		write(STDOUT_FILENO, p, 2);
		r = handle_args(exe_return);
		if (r == END_OF_FILE || r == EXIT)
		{
			if (r == END_OF_FILE)
				write(STDOUT_FILENO, line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*exe_return);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exe_return);
}
