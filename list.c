#include "main.h"

alias_t *add_alias(alias_t **h, char *n, char *v);
void free_alias(alias_t *h);
list_t *add_node_end(list_t **h, char *d);
void free_list(list_t *h);

/**
 * add_alias - This program adds a new node at the end of the alias
 * @h: A pointer to be used
 * @n: The node to be added
 * @v: The value of node to be added
 * Return: If an error occurs return null
 */
alias_t *add_alias(alias_t **h, char *n, char *v)
{
	alias_t *node = malloc(sizeof(alias_t));
	alias_t *l;

	if (!node)
		return (NULL);

	node->next = NULL;
	node->name = malloc(sizeof(char) * (_strlen(n) + 1));
	if (!node->name)
	{
		free(node);
		return (NULL);
	}
	node->value = v;
	_strcpy(node->name, n);

	if (*h)
	{
		l = *h;
		while (l->next != NULL)
			l = l->next;
		l->next = node;
	}
	else
		*h = node;

	return (node);
}

/**
 * add_node_end - A program that adds a node to the end of a list_t
 * @h: The pointer to be used
 * @d: The directory the new node will contain
 * Return: null if an error occurs
 */
list_t *add_node_end(list_t **h, char *d)
{
	list_t *node = malloc(sizeof(list_t));
	list_t *l;

	if (!node)
		return (NULL);

	node->d = d;
	node->next = NULL;

	if (*h)
	{
		l = *h;
		while (l->next != NULL)
			l = l->next;
		l->next = node;
	}
	else
		*h = node;

	return (node);
}

/**
 * free_alias - A program the frees an alias
 * @h: the list to be used
 */
void free_alias(alias_t *h)
{
	alias_t *x;

	while (h)
	{
		x = h->next;
		free(h->name);
		free(h->value);
		free(h);
		h = x;
	}
}

/**
 * free_list - A program that frees a linked list
 * @h: The list to be used
 */
void free_list(list_t *h)
{
	list_t *x;

	while (h)
	{
		x = h->next;
		free(h->d);
		free(h);
		h = x;
	}
}
