/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:46:04 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/03 20:07:35 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			str_contains(const char *str, const char *lst)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (lst[j])
		{
			if (str[i] == lst[j])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

int			get_path_len(char **str_ptr)
{
	int		i;
	char	*str;

	str = *str_ptr;
	i = 0;
	if (ft_isspace(str[i]))
	{
		*str_ptr += 1;
		return (get_path_len(str_ptr));
	}
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

void		set_fd(t_cmdlist *new, int *fd, int which_fd)
{
	t_fdlist	*new_fd;
	t_fdlist	**list;

	if (*fd < 0)
		return ;
	list = NULL;
	ft_printf("then fd is: %d\n", *fd);
	ft_printf("which_fd is: %d\n", which_fd);
	new_fd = fdlist_new(*fd);
	if (!new_fd)
	{
		*fd = -42;
		return ;
	}
	ft_printf("FINAL FD: %d\n", new_fd->fd);
	fdlist_print(new_fd);
	if (which_fd == 0)
		list = &(new->fd_in);
	else if (which_fd == 1)
		list = &(new->fd_out);
	else if (which_fd == 2)
		list = &(new->fd_out_err);
	fdlist_add_back(list, new_fd);
}

void		set_which_fd(char *cmd, int index, int *which_fd)
{
	int		output_to_redir;

	if (index == 0 || cmd[index] == '<')
	{
		*which_fd = 0;
		return ;
	}
	*which_fd = 1;
	output_to_redir = index - 1;
	if (ft_isdigit(cmd[output_to_redir]))
	{
		if (output_to_redir == 0 || ft_isspace(cmd[output_to_redir - 1]))
		{
			if (cmd[output_to_redir] == '1')
				*which_fd = 1;
			else if (cmd[output_to_redir] == '2')
				*which_fd = 2;
			else
			{
				ft_putstr_fd("minishell: you can only redirect stdin and stdout\n", 2);
				exit(1);
			}
		}
	}
}
