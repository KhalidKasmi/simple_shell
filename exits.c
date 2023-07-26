#include "shell.h"


/**
 **_strchr - finds a character in a string
 *@str: the string to be parsed
 *@ch: the character to look for
 *
 *Return: pointer to located character in string
 */
char *_strchr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}







/**
 **_strncpy - copies a string given
 *@dest: the destination string to be copied to
 *@src: the source string
 *@num: the number of characters to be copied
 *Return: concatenated string
 */
char *_strncpy(char *dest, char *src, int num)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < num - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@num: maximum number of bytes to use
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int num)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < num)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < num)
		dest[i] = '\0';
	return (s);
}

