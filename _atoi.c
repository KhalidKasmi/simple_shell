#include "shell.h"

/**
 * checkinteractive - determine whether the shell is in interactive mode
 * @inf1: address structure
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int checkinteractive(info_t *inf1)
{
return (isatty(STDIN_FILENO) && inf1->readfd <= 2);
}

/**
 * checkdelim - checks the character if is a delimeter
 * @c: the char to check
 * @del: the delimeter string
 * Return: 1 if true, 0 if false
 */
int checkdelim(char c, char *del)
{
while (*del)
if (*del++ == c)
return (1);
return (0);
}

/**
 * checkalpha - checks if the character is an  alphabetic character
 * @c: The character to check
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int checkalpha(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}

/**
 * _atoi -  transforms a given string into an integer
 * @str: the string to be processed
 * Return: 0 if no numeric characters found, the resulting integer otherwise
 */

int _atoi(char *str)
{
int i, sign = 1, flag = 0, output;
unsigned int res = 0;

for (i = 0; str[i] != '\0' && flag != 2; i++) {
if (str[i] == '-')
sign *= -1;

if (str[i] >= '0' && str[i] <= '9') {
flag = 1;
res *= 10;
res += (s[i] - '0');
    }
else if (flag == 1)
flag = 2;
  }

if (sign == -1)
output = -res;
else
output = res;

return (output);
}
