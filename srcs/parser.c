/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 17:50:05 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/25 11:45:31 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	raise_error(void)
{
	ft_putstr_fd("minishell: parsing error, please close quote", 2);
	ft_putendl_fd(" or double quote", 2);
	return (-1);
}

static int	nb_arg(char *line, char delim)
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
		if (line[i] == delim && !in_quote && !in_dquote)
			n_cmd++;
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
**   array terminated by null value
*/

char		**parse_line(char *line)
{
	char	**res;
	int		i;
	int		j;
	int		prev_delim;

	if (nb_arg(line, ';') < 0 ||
		!(res = ft_memalloc((nb_arg(line, ';') + 1) * sizeof(char *))))
		return (NULL);
	prev_delim = 0;
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == ';')
		{
			res[j++] = ft_substr(line, prev_delim, i - prev_delim);
			while (line[i + 1] == ' ')
				i++;
			prev_delim = i + 1;
		}
		else if (line[i] == '"' || line[i] == '\'')
			i += ft_index(line + i + 1, line[i]) + 1;
	}
	res[j] = ft_substr(line, prev_delim, i - prev_delim);
	return (res);
}

/*
** Make a ft_substr(str, start, len), then remove quotes
** at the beggining and at the end of substr
** Alloc a new char *
*/

static char	*ft_substr_trim(char *str, int start, int len)
{
	char	*substr;
	int		i;
	char	*res;

	i = 0;
	if (!(substr = ft_substr(str, start, len)))
		return (NULL);
	res = trim_quotes(substr);
	free(substr);
	return (res);
}

/*
** Parse commands and split in multiple args
** - line : char * of one or more args, separated by ' '
** Return value:
** - char **, each elem of this array is an independant arg
**   array terminated by null value
*/

char		**parse_command(char *cmd)
{
	char	**res;
	int		i;
	int		j;
	int		prev_delim;

	if (nb_arg(cmd, ' ') < 0 ||
		!(res = ft_memalloc((nb_arg(cmd, ' ') + 1) * sizeof(char *))))
		return (NULL);
	i = -1;
	j = 0;
	prev_delim = 0;
	while (cmd[++i])
	{
		if (cmd[i] == ' ')
		{
			res[j++] = ft_substr_trim(cmd, prev_delim, i - prev_delim);
			while (cmd[i + 1] == ' ')
				i++;
			prev_delim = i + 1;
		}
		else if (cmd[i] == '"' || cmd[i] == '\'')
			i += ft_index(cmd + i + 1, cmd[i]) + 1;
	}
	res[j] = ft_substr_trim(cmd, prev_delim, i - prev_delim);
	return (res);
}
