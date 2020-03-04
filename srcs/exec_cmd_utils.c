/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 16:57:01 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/04 17:04:58 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sub_exec(char *cmd_path, char **argv, char **envp)
{
	reset_signals();
	execve(cmd_path, argv, envp);
	exit(handle_cmd_error(errno, cmd_path));
}

int		free_and_return(char ***ptr, int ret_val)
{
	if (ptr && *ptr)
	{
		free_str_arr(*ptr);
		free(*ptr);
	}
	return (ret_val);
}

int		handle_cmd_error(int error_type, const char *cmd)
{
	if (cmd)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
	}
	if (error_type == 1)
	{
		if (cmd)
			ft_putendl_fd(": command not found", 2);
		return (127);
	}
	else
	{
		if (cmd)
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), 2);
		}
		return (errno);
	}
}

void	trim_path(t_cmdlist *commands)
{
	int		i;
	char	*path;

	if (!commands)
		return ;
	i = 0;
	while (commands)
	{
		path = ft_strtrim(commands->command, " ");
		free(commands->command);
		commands->command = path;
		commands = commands->next;
	}
}

int		get_last_fd(t_fdlist *list)
{
	while (list && list->next)
		list = list->next;
	return (list->fd);
}
