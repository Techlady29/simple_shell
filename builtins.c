#include "main.h"


int (*get_builtin(char *command))(char **args, char **front);
int shellof_exit(char **args, char **front);
int shellof_cd(char **args, char __attribute__((__unused__)) **front);
int shellof_help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin - this matches a command with a corresponding
 * shellof builtin function
 * @command: the command to match
 * Return: a function pointer to the corresponding builtin
 */


int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", shellof_exit },
		{ "env", shellof_env },
		{ "setenv", shellof_setenv },
		{ "unsetenv", shellof_unsetenv },
		{ "cd", shellof_cd },
		{ "alias", shellof_alias },
		{ "help", shellof_help },
		{ NULL, NULL }
	};
	int j;

	for (j = 0; funcs[j].name; j++)
	{
		if (_strcmp(funcs[j].name, command) == 0)
			break;
	}
	return (funcs[j].f);
}

/**
 * shellof_exit -this causes normal process termination
 * for the shellby shell
 * @args: an array of arguments containing exit value
 * @front: a double pointer to the beginning of args
 * Return: -3 if there are no arguments,
 * if the given exit value is invalid - 2
 * O/w - exits with the given status value
 * Description: upon returning -3, the program exits back in the main function
 */

int shellof_exit(char **args, char **front)
{
	int j, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			j = 1;
			len_of_int++;
		}
		for (; args[0][j]; j++)
		{
			if (j <= len_of_int && args[0][j] >= '0' && args[0][j] <= '9')
				num = (num * 10) + (args[0][j] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_mem(args, front);
	free_env();
	free_alias(aliases);
	exit(num);
}

/**
 * shellof_cd - this changes the current directory of the shellof process
 * @args: an array of arguments
 * @front: a double pointer to the beginning of args
 * Return: 2 if the given string is not a directory
 * if an error occurs - -1, otherwise - 0
 */

int shellof_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (shellof_unsetenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (shellof_unsetenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * shellof_help - this displays information about shellof builtin commands
 * @args: an array of arguments
 * @front: a pointer to the beginning of args
 * Return: -1 if an error occurs, otherwise - 0
 */

int shellof_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		help_all();
	else if (_strcmp(args[0], "alias") == 0)
		help_alias();
	else if (_strcmp(args[0], "cd") == 0)
		help_cd();
	else if (_strcmp(args[0], "exit") == 0)
		help_exit();
	else if (_strcmp(args[0], "env") == 0)
		help_env();
	else if (_strcmp(args[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(args[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
