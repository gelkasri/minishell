/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:39:13 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/04 16:21:01 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include <stdio.h>

static void		get_fd_flat(int *fd, char *cmd, int *index)
{
	int			i;
	struct stat	buf;

	*index += 1;
	i = *index;
	while (ft_isdigit(cmd[i]))
		i++;
	if (ft_isspace(cmd[i]) || cmd[i] == '\0')
	{
		*fd = ft_atoi(cmd + (*index));
		if (fstat(*fd, &buf) == -1)
			*fd = -10;
	}
}

static void		get_fd_from_path(int *fd, char *cmd, int type)
{
	int		len;

	if (*fd != -42)
		return ;
	len = get_path_len(&cmd);
	cmd = ft_substr(cmd, 0, len);
	if (!cmd)
		return ;
	if (type == '<')
		*fd = open(cmd, O_RDONLY);
	else if (type == '>')
		*fd = open(cmd, O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (type == '>' + 1)
		*fd = open(cmd, O_WRONLY | O_CREAT | O_APPEND,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	free(cmd);
}

static int		set_fds(char *cmd, int index, t_cmdlist *new)
{
	int			i;
	int			fd;
	int			which_fd;
	int			redir;

	redir = index;
	fd = -42;
	set_which_fd(cmd, index, &which_fd);
	if (which_fd < 0)
		return (which_fd);
	while (cmd[index] == '<' || cmd[index] == '>')
		index++;
	if (cmd[index] == '&')
		get_fd_flat(&fd, cmd, &index);
	i = index;
	if (cmd[redir] == '<')
	{
		get_fd_from_path(&fd, cmd + index, '<');
		set_fd(new, &fd, which_fd);
	}
	else if (cmd[redir] == '>')
	{
		if (cmd[redir + 1] == '>')
		{
			get_fd_from_path(&fd, cmd + index, '>' + 1);
			set_fd(new, &fd, which_fd);
		}
		else
		{
			get_fd_from_path(&fd, cmd + index, '>');
			set_fd(new, &fd, which_fd);
		}
	}
	return (fd);
}

t_cmdlist		*get_cmd_params(char *cmd_from_arr)
{
	t_cmdlist	*new;
	int			i;
	int			err;
	char		*cmd;

	cmd = ft_strdup(cmd_from_arr);
	new = cmdlist_new(NULL);
	if (!new)
		return (NULL);
	while ((i = str_contains(cmd, "<>")) != -1)
	{
		err = set_fds(cmd, i, new);
		if (err == -21)
			return ((t_cmdlist*)free_return((void*)new, (void*)cmd, NULL));
		if (err < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putendl_fd(strerror(errno), 2);
			return ((t_cmdlist*)free_return((void*)new, (void*)cmd, NULL));
		}
		if (!(cmd = remove_param(cmd, i)))
			return ((t_cmdlist*)free_return((void*)new, NULL, NULL));
	}
	new->command = cmd;
	if (DEBUG)
		cmdlist_print(new);
	return (new);
}

/*
** replace split(line, '|') to take care of pipes that are in quotes
*/

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
		{
			free_str_arr(split);
			free(split);
			return (end_parser(final));
		}
		cmdlist_add_back(&final, new);
		i++;
	}
	free_str_arr(split);
	free(split);
	return (final);
}
