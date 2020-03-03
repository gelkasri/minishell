/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:39:13 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/03 20:05:41 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include <stdio.h>

static t_cmdlist	*end_parser(t_cmdlist *cmdlist)
{
	cmdlist_clear(&cmdlist, free);
	return (NULL);
}

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
	ft_printf("path: %s|\n", cmd);
	if (!cmd)
		return ;
	if (type == '<')
		*fd = open(cmd, O_RDONLY);
	else if (type == '>')
		*fd = open(cmd, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	else if (type == '>' + 1)
		*fd = open(cmd, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
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
	while (cmd[index] == '<' || cmd[index] == '>')
		index++;
	ft_printf("here: %s|\n", cmd + index);
	if (cmd[index] == '&')
		get_fd_flat(&fd, cmd, &index);
	i = index;
	if (cmd[redir] == '<')
	{
		ft_printf("redir: <\nfd: %d\n", fd);
		get_fd_from_path(&fd, cmd + index, '<');
		ft_printf("now, fd is: %d\n", fd);
		set_fd(new, &fd, which_fd);
	}
	else if (cmd[redir] == '>')
	{
		if (cmd[redir + 1] == '>')
		{
			ft_printf("redir: >>\nfd: %d\n", fd);
			get_fd_from_path(&fd, cmd + index, '>' + 1);
			ft_printf("now, fd is: %d\n", fd);
			set_fd(new, &fd, which_fd);
		}
		else
		{
			ft_printf("redir: >\nfd: %d\n", fd);
			get_fd_from_path(&fd, cmd + index, '>');
			ft_printf("now, fd is: %d\n", fd);
			set_fd(new, &fd, which_fd);
		}
	}
	return (fd);
}

t_cmdlist		*get_cmd_params(char *cmd)
{
	t_cmdlist	*new;
	int			i;
	int			err;

	new = cmdlist_new(NULL);
	while (new && (i = str_contains(cmd, "<>")))
	{
		err = set_fds(cmd, i, new);
		ft_printf("err is : %d\n", err);
		if (err < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putendl_fd(strerror(errno), 2);
			exit(1);
		}
		// if (!(cmd = remove_param(cmd, i)))
		// 	return (NULL);
		cmdlist_print(new);
		exit(1);
	}
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
		cmdlist_add_back(&final, new);
		i++;
	}
	free_str_arr(split);
	free(split);
	return (final);
}
