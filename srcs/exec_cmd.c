/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:57:20 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/26 11:16:02 by mle-moni         ###   ########.fr       */
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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (error_type == 1)
	{
		ft_putendl_fd(": command not found", 2);
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
	split = parse_command(cmd);
	if (split[0] == NULL)
		return (free_and_return(&split, 0));
	ret = exec_builtins(split, env_list);
	if (ret >= 0)
		return (free_and_return(&split, ret));
	if (!(path = find_path(split[0], env_list)))
		path = check_path(NULL, split[0]);
	if (path && !(id_child = fork()))
	{
		execve(path, split, get_env_array(env_list));
		exit(handle_error(errno, path));
	}
	waitpid(id_child, &ret, 0);
	ret = WEXITSTATUS(ret);
	if (!path)
		ret = handle_error(1, split[0]);
	free(path);
	return (free_and_return(&split, ret));
}

static int		get_exit_status(t_list **env_list)
{
	char	*str;
	int		res;

	if ((str = get_env_var("?", env_list)))
		res = ft_atoi(str);
	else
		res = 0;
	free(str);
	return (res);
}

int				exec_line(char *line, t_list **env_list)
{
	char	**commands;
	int		i;
	int		ret;
	char	*tmp;

	if (ft_strlen(line) == 0)
		return (get_exit_status(env_list));
	commands = parse_line(line);
	if (!commands)
		return (1);
	i = 0;
	ret = 0;
	while (commands[i] && ft_strlen(commands[i]))
	{
		tmp = apply_env_var(commands[i++], env_list);
		if (!tmp)
			ret = 1;
		else
			ret = exec_cmd(tmp, env_list);
		free(tmp);
	}
	free_str_arr(commands);
	free(commands);
	return (ret);
}
