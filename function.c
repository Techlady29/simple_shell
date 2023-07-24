#include "main.h"

int _strlen(const char *t);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t m);

/**
 * _strlen - A program that returns the length of a string
 * @t: The pointer to be used
 * Return: The length of a string
 */
int _strlen(const char *t)
{
	int l = 0;

	if (!t)
		return (l);
	for (l = 0; t[l]; l++)
		;
	return (l);
}

/**
 * _strcpy - A program that copies two string
 * @dest: The pointer to be used
 * @src: The pointer to be used
 * Return: The pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	size_t j;

	for (j = 0; src[j] != '\0'; j++)
		dest[j] = src[j];
	dest[j] = '\0';
	return (dest);
}

/**
 * _strcat - A program that Concantenates destination string to
 *           source string
 * @dest: The pointer to be used
 * @src: The pointer to be used
 * Return: The pointer to the string
 */
char *_strcat(char *dest, const char *src)
{
	char *temp;
	const char *pemt;

	temp = dest;
	pemt =  src;

	while (*temp != '\0')
		temp++;

	while (*pemt != '\0')
		*temp++ = *pemt++;
	*temp = '\0';
	return (dest);
}

/**
 * _strncat - A program that concantenates two strings
 * @dest: A pointer to be used
 * @src: A pointer to be used
 * @m: the bytes
 * Return: The pointer to destination string
 */
char *_strncat(char *dest, const char *src, size_t m)
{
	size_t len = _strlen(dest);
	size_t j;

	for (j = 0; j < m && src[j] != '\0'; j++)
		dest[len + j] = src[j];
	dest[len + j] = '\0';

	return (dest);
}
