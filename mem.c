#include "main.h"

/**
 * memfree - A program that frees a pointer
 * @p: The pointer to be freed
 * Return: 1 if pointer is frred, otherwise return 0
 */
int memfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	else
		return (0);
}
