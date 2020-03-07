/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:39:13 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/07 11:46:43 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

void			*free_return(void *ptr, void *ptr2, void *ret_val)
{
	free(ptr);
	free(ptr2);
	return (ret_val);
}

static void		get_fd_flat(t_fdsetter *fd, char *cmd, int *index)
{
	int			i;
	struct stat	buf;

	*index += 1;
	i = *index;
	while (ft_isdigit(cmd[i]))
		i++;
	if (ft_isspace(cmd[i]) || cmd[i] == '\0')
	{
		fd->fd = ft_atoi(cmd + (*index));
		if (fd->fd == 1 || (fd->fd == 2 && fd->which == 2))
		{
			fd->fd = -15;
			return ;
		}
		if (fstat(fd->fd, &buf) == -1)
			fd->fd = -10;
	}
}

static int		set_fds(char *cmd, int index, t_cmdlist *new)
{
	t_fdsetter	fd;

	fd.redir = index;
	fd.fd = -42;
	set_which_fd(cmd, index, &(fd.which));
	if (fd.which < 0)
		return (fd.which);
	while (cmd[index] == '<' || cmd[index] == '>')
		index++;
	if (cmd[index] == '&')
		get_fd_flat(&fd, cmd, &index);
	if (fd.fd == -15)
		return (0);
	if (cmd[fd.redir] == '<')
		fd_setter(new, &fd, cmd + index, '<');
	else if (cmd[fd.redir] == '>')
	{
		if (cmd[fd.redir + 1] == '>')
			fd_setter(new, &fd, cmd + index, '>' + 1);
		else
			fd_setter(new, &fd, cmd + index, '>');
	}
	return (fd.fd);
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
	split = split_pipes(line);
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
