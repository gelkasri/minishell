/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_setter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:06:02 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/04 17:22:22 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static void	set_fd(t_cmdlist *new, int *fd, int which_fd)
{
	t_fdlist	*new_fd;
	t_fdlist	**list;

	if (*fd < 0)
		return ;
	list = NULL;
	new_fd = fdlist_new(*fd);
	if (!new_fd)
	{
		*fd = -42;
		return ;
	}
	if (which_fd == 0)
		list = &(new->fd_in);
	else if (which_fd == 1)
		list = &(new->fd_out);
	else if (which_fd == 2)
		list = &(new->fd_out_err);
	fdlist_add_back(list, new_fd);
}

static void	get_fd_from_path(int *fd, char *cmd, int type)
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

void		fd_setter(t_cmdlist *new, t_fdsetter *fd, char *cmd, int type)
{
	get_fd_from_path(&(fd->fd), cmd, type);
	set_fd(new, &(fd->fd), fd->which);
}
