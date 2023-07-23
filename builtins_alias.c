#include "main.h"

int shellof_alias(char **args, char __attribute__((__unused__)) **front);
void get_alias(char *var_name, char *value);
void print_alias(alias_t *alias);



/**
 * get_alias - this will set an existing alias 'name' with a new value
 * 'value' or creates a new alias with 'name' and 'value'
 * @var_name: name of alias
 * @value: the value of the alias. First character is a '='.
 */

void get_alias(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int len, f, e;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (f = 0, e = 0; value[f]; f++)
	{
		if (value[f] != '\'' && value[f] != '"')
			new_value[e++] = value[f];
	}
	new_value[e] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias(&aliases, var_name, new_value);
}

/**
 * shellof_alias - this builtin command either prints all aliases, specific
 * aliases, or sets an alias
 * @args: An array of arguments
 * @front: A double pointer to the beginning of args
 * Return: If an error occurs -1.
 *         Otherwise - 0.
 */

int shellof_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int d, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (d = 0; args[d]; d++)
	{
		temp = aliases;
		value = _strchr(args[d], '=');
		if (!value)
		{
			while (temp)
			{
				if (_strcmp(args[d], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_error(args + d, 1);
		}
		else
			get_alias(args[d], value);
	}
	return (ret);
}


/**
 * print_alias - this prints the alias in the format name = 'value'
 * @alias: the pointer to an alias
 */

void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}

/**
 * replace_aliases - this goes through the arguments and replace any
 * matching alias with their value
 * @args: 2D pointer to the arguments
 * Return: 2D pointer to the arguments
 */

char **replace_aliases(char **args)
{
	alias_t *temp;
	int d;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (d = 0; args[d]; d++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[d], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(temp->value) + 1));
				if (!new_value)
				{
					free_mem(args, args);
					return (NULL);
				}
				_strcpy(new_value, temp->value);
				free(args[d]);
				args[d] = new_value;
				d--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
