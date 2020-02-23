
#include "minishell.h"

/*
** Parse line of multiples commands, and split in multiple commands
** Return a char **, each elem of this array is an independant command to exec
*/

char	**parse_line(char *line)
{
	char **res;

	res = ft_split(line, ';');
	return (res);
}
