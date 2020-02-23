
#include "minishell.h"

static int	raise_error()
{
	ft_putendl_fd("minishell: parsing error, please close quote or double quote", 2);
	return (-1);
}

static int	nb_cmd(char *line)
{
	int i;
	int in_quote;
	int in_dquote;
	int n_cmd;

	i = 0;
	in_quote = 0;
	in_dquote = 0;
	n_cmd = *line ? 1 : 0;
	while (line[i])
	{
		if (line[i] == ';' && !in_quote && !in_dquote)
		{
			n_cmd++;
			in_quote = 0;
			in_dquote = 0;
		}
		else if (line[i] == '"' && !in_quote)
			in_dquote = (in_dquote + 1) % 2;
		else if (line[i] == '\'' && !in_dquote)
			in_quote = (in_quote + 1) % 2;
		i++;
	}
	if (in_quote || in_dquote)
		return (raise_error());
	return (n_cmd);
}

/*
** Parse line of multiples commands, and split in multiple commands
** - line : char * of one or more commands, separated by ';'
** Return value:
** - char **, each elem of this array is an independant command to exec
*/

char		**parse_line(char *line)
{
	char	**res;
	int		i;
	int		n_cmd;

	i = 0;
	n_cmd = nb_cmd(line);
	if (n_cmd < 0)
		return (NULL);
	ft_printf("nb_cmd=%d\n", n_cmd);
	while (line[i])
	{
		i++;
	}
	res = ft_split(line, ';');
	return (res);
}
