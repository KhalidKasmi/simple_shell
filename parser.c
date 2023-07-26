#include "shell.h"

/**
 * checkcmd - checks if a file is a command
 * @inf: the info struct
 * @p: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int checkcmd(info_t *inf, char *p) {
  struct stat st;

  (void)inf;
  if (!p || stat(p, &st))
    return (0);

  if (st.st_mode & S_IFREG) {
    return (1);
  }
  return (0);
}

/**
 * find_path - finds this command in the PATH string
 * @inf: the info struct
 * @pathstr: the PATH string
 * @cmd: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *find_path(info_t *inf, char *pathstr, char *cmd) {
  int i = 0, curr_pos = 0;
  char *path;

  if (!pathstr)
    return (NULL);
  if ((_strlen(cmd) > 2) && starts_with(cmd, "./")) {
    if (checkcmd(inf, cmd))
      return (cmd);
  }
  while (1) {
    if (!pathstr[i] || pathstr[i] == ':') {
      path = dup_chars(pathstr, curr_pos, i);
      if (!*path)
        _strcat(path, cmd);
      else {
        _strcat(path, "/");
        _strcat(path, cmd);
      }
      if (checkcmd(inf, path))
        return (path);
      if (!pathstr[i])
        break;
      curr_pos = i;
    }
    i++;
  }
  return (NULL);
}







/**
 * dup_chars - make a duplicate of  characters
 * @pathstr: the PATH string
 * @strt: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int strt, int stop) {
  static char buf[1024];
  int i = 0, k = 0;

  for (k = 0, i = strt; i < stop; i++)
    if (pathstr[i] != ':')
      buf[k++] = pathstr[i];
  buf[k] = 0;
  return (buf);
}

