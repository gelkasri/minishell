/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:57:20 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/23 18:47:17 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

static int		free_and_return(char ***ptr, int ret_val)
{
	if (ptr && *ptr)
	{
		free_str_arr(*ptr);
		free(*ptr);
	}
	return (ret_val);
}

static int		handle_error(int error_type, const char *cmd)
{
	ft_putstr_fd(cmd, 2);
	if (error_type == 1)
	{
		ft_putendl_fd(": unknown command", 2);
		return (127);
	}
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (errno);
	}
}

static int		exec_cmd(char *cmd, t_list **env_list)
{
	pid_t	id_child;
	int		ret;
	char	*path;
	char	**split;

	id_child = -1;
	split = ft_split(cmd, ' ');
	ret = exec_builtins(split, env_list);
	if (ret >= 0)
		return (free_and_return(&split, ret));
	path = find_path(split[0], env_list);
	if (!path)
		path = check_path(NULL, split[0]);
	if (path && !(id_child = fork()))
	{
		execve(path, split, get_env_array(env_list));
		exit(handle_error(errno, path));
	}
	waitpid(id_child, &ret, 0);
	ret = WEXITSTATUS(ret);
	if (!path)
		ret = handle_error(1, cmd);
	free(path);
	return (free_and_return(&split, ret));
}

int				exec_line(char *line, t_list **env_list)
{
	char	**commands;
	int		i;
	int		ret;

	commands = ft_split(line, ';');
	i = 0;
	ret = 0;
	while (commands[i])
		ret = exec_cmd(commands[i++], env_list);
	free_str_arr(commands);
	free(commands);
	return (ret);
}
