#include "shell.h"

/**
 * _myenv - exhibits the current environment
 * @inf: Structure containing potential arguments. Utilized to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * _getenv - obtains the value of an environment variable
 * @inf: Structure holding potential arguments. Employed to preserve constant function prototypes
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *inf, const char *name)
{
	list_t *node = inf->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv -  Bring a new environmental variable into existence,,
 *             or adjust an existing one
 * @inf: Structure holding prospective arguments. Harnessed to preserve constant function prototype.
 * 
 *  Return: Always 0
 */
int _mysetenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Delete an environment variable
 * @inf: Structure holding possible arguments. Used to keep
 *         function signature the same.
 * Return: Always 0
 */
int _myunsetenv(info_t *inf)
{
	int i;

	if (inf->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= inf->argc; i++)
		_unsetenv(inf, inf->argv[i]);

	return (0);
}

/**
 * populate_env_list -  fills the environ linked list
 * @inf: Structure with potential arguments. Used to maintain
 *         consistent function prototype..
 * Return: Always 0
 */
int populate_env_list(info_t *inf)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	inf->env = node;
	return (0);
}
