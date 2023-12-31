#include "shell.h"

/**
 * get_history_file - gets the history file
 * @inf: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *inf)
{
	char *buf, *dir;

	dir = _getenv(inf, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * read_history - reads history from a file given
 * @inf: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *inf)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(inf);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(inf, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(inf, buf + last, linecount++);
	free(buf);
	inf->histcount = linecount;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	remember_history(inf);
	return (inf->histcount);
}




/**
 * write_history - creates a new file or appends to an existing file
 * @inf: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *inf)
{
	ssize_t fd;
	char *filename = get_history_file(inf);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = inf->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
 

/**
 * build_history_list - adds an entry to a linked list of history
 * @inf: Structure containing potential arguments. Used to keep constant function parameters
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *inf, char *buf, int linecount)
{
	list_t *node = NULL;

	if (inf->history)
		node = inf->history;
	add_node_end(&node, buf, linecount);

	if (!inf->history)
		inf->history = node;
	return (0);
}

/**
 * remember_history - remembers the history linked list after changes
 * @inf: Structure holding potential arguments. Used to keep constant function parameters
 *
 * Return: the new histcount
 */
int remember_history(info_t *inf)
{
	list_t *node = inf->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (inf->histcount = i);
}
