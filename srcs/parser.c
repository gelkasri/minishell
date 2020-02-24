/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 17:50:05 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/23 17:52:35 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	raise_error(void)
{
	ft_putendl_fd("minishell: parsing error, please close quote \
					or double quote", 2);
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

	i = 0;
	j = 0;
	prev_delim = 0;
	if (nb_cmd(line) < 0 ||
		!(res = ft_memalloc((nb_cmd(line) + 1) * sizeof(char *))))
		return (NULL);
	while (line[i])
	{
		if (line[i] == ';')
		{
			res[j++] = ft_substr(line, prev_delim, i - prev_delim);
			prev_delim = i + 1;
		}
		else if (line[i] == '"' || line[i] == '\'')
			i += ft_index(line + i + 1, line[i]) + 1;
		i++;
	}
	res[j] = ft_substr(line, prev_delim, i - prev_delim);
	return (res);
}
