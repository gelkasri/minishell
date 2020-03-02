/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:39:13 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/02 17:53:35 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>

/*
static int			set_type_and_index(char *src, int i, t_cmdlist *new)
{
	while (src[i])
	{
		if (src[i] == '<')
		{
			new->type = FROM_FILE;
			return (i);
		}
		else if (src[i] == '>')
		{
			if (src[i + 1] == '>')
			{
				new->type = TO_FILE_APPEND;
				return (i);
			}
			new->type = TO_FILE;
			return (i);
		}
		else if (src[i] == '|')
		{
			new->type = PIPE;
			return (i);
		}
		i++;
	}
	return (-1);
}
*/

static t_cmdlist	*end_parser(t_cmdlist *cmdlist)
{
	cmdlist_clear(&cmdlist, free);
	return (NULL);
}

/*
t_cmdlist			*cmdparser(char *line)
{
	t_cmdlist	*final;
	int			i;
	int			new_i;
	t_cmdlist	*new;

	i = 0;
	final = NULL;
	while (line[i])
	{
		new = cmdlist_new(NULL, -1, -1);
		if (!new)
			return (end_parser(final));
		new_i = set_type_and_index(line, i, new);
		if (new_i == -1)
			break ;
		cmdlist_set(new, ft_substr(line, i, new_i - i), -42, 1);
		if (!(new->command))
			return (end_parser(final));
		i = new_i + ((new->type == TO_FILE_APPEND) ? 2 : 1);
		cmdlist_add_back(&final, new);
	}
	new_i = ft_strlen(line);
	cmdlist_set(new, ft_substr(line, i, new_i - i), LAST, 1);
	if (!(new->command))
		return (end_parser(final));
	cmdlist_add_back(&final, new);
	return (final);
}
*/

t_cmdlist		*get_cmd_params(char *cmd)
{
	t_cmdlist	*new;

	return (new);
}

t_cmdlist		*cmdparser(char *line)
{
	char		**split;
	int			i;
	t_cmdlist	*final;
	t_cmdlist	*new;

	i = 0;
	final = NULL;
	split = ft_split(line, '|');
	if (!split)
		return (NULL);
	while (split[i])
	{
		new = get_cmd_params(split[i]);
		if (!new)
			return (end_parser(final));
		list_add_back((void **)&final, (void *)new);
		i++;
	}
	free_str_arr(split);
	free(split);
	return (final);
}
