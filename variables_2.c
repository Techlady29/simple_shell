#include "main.h"

void split_line(char **l, ssize_t r);
ssize_t get_new_line(char *l);
void check_op(char *l, ssize_t *len);

/**
 * split_line - A program that splits a line standard input
 * @l: The double pointer to standard input
 * @r: The length of a line
 */
void split_line(char **l, ssize_t r)
{
	char *line, *new_line;
	char p, c, n;
	size_t o, q;
	ssize_t len;

	len = get_new_line(*l);
	if (len == r - 1)
		return;
	new_line = malloc(len + 1);
	if (!new_line)
		return;
	q = 0;
	line = *l;
	for (o = 0; line[o]; o++)
	{
		c = line[o];
		n = line[o + 1];
		if (o != 0)
		{
			p = line[o - 1];
			if (c == ';')
			{
				if (n == ';' && p != ' ' && p != ';')
				{
					new_line[q++] = ' ';
					new_line[q++] = ';';
					continue;
				}
				else if (p == ';' && n != ' ')
				{
					new_line[q++] = ';';
					new_line[q++] = ' ';
					continue;
				}
				if (p != ' ')
					new_line[q++] = ' ';
				new_line[q++] = ';';
				if (n != ' ')
					new_line[q++] = ' ';
				continue;
			}
			else if (c == '&')
			{
				if (n == '&' && p != ' ')
					new_line[q++] = ' ';
				else if (p == '&' && n != ' ')
				{
					new_line[q++] = '&';
					new_line[q++] = ' ';
					continue;
				}
			}
			else if (c == '|')
			{
				if (n == '|' && p != ' ')
					new_line[q++]  = ' ';
				else if (p == '|' && n != ' ')
				{
					new_line[q++] = '|';
					new_line[q++] = ' ';
					continue;
				}
			}
		}
		else if (c == ';')
		{
			if (o != 0 && line[o - 1] != ' ')
				new_line[q++] = ' ';
			new_line[q++] = ';';
			if (n != ' ' && n != ';')
				new_line[q++] = ' ';
			continue;
		}
		new_line[q++] = line[o];
	}
	new_line[q] = '\0';

	free(*l);
	*l = new_line;
}

/**
 * get_new_line - A program that generates the length of a line
 * @l: This is the line to be used
 * Return: The new length of a line
 */

ssize_t get_new_line(char *l)
{
	size_t r;
	ssize_t len = 0;
	char c, n;

	for (r = 0; l[r]; r++)
	{
		c = l[r];
		n = l[r + 1];
		if (c == '#')
		{
			if (r == 0 || l[r - 1] == ' ')
			{
				l[r] = '\0';
				break;
			}
		}
		else if (r != 0)
		{
			if (c == ';')
			{
				if (n == ';' && l[r - 1] != ' ' && l[r - 1] != ';')
				{
					len += 2;
					continue;
				}
				else if (l[r - 1] == ';' && n != ' ')
				{
					len += 2;
					continue;
				}
				if (l[r - 1] != ' ')
					len++;
				if (n != ' ')
					len++;
			}
			else
				check_op(&l[r], &len);
		}
		else if (c == ';')
		{
			if (r != 0 && l[r - 1] != ' ')
				len++;
			if (n != ' ' && n != ';')
				len++;
		}
		len++;
	}
	return (len);
}
/**
 * check_op - A program that checks if there is a logical operator
 *            in a line
 * @l: A pointer to beu sed
 * @len: A pointer to be used form get_new_line
 */
void check_op(char *l, ssize_t *len)
{
	char p, c, n;

	p = *(l - 1);
	c = *l;
	n = *(l + 1);

	if (c == '&')
	{
		if (n == '&' && p != ' ')
			(*len)++;
		else if (p == '&' && n != ' ')
			(*len)++;
	}
	else if (c == '|')
	{
		if (n == '|' && p != ' ')
			(*len)++;
		else if (p == '|' && n != ' ')
			(*len)++;
	}
}
