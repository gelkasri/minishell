/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:57:20 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/02 10:08:08 by gel-kasr         ###   ########.fr       */
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

static void		sub_exec(char *cmd_path, char **argv, char **envp)
{
	reset_signals();
	execve(cmd_path, argv, envp);
	exit(handle_error(errno, cmd_path));
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
		sub_exec(path, split, get_env_array(env_list));
	ignore_signals();
	waitpid(id_child, &ret, 0);
	ret = get_child_exit_status(ret);
	if (!path)
		ret = handle_error(1, split[0]);
	free(path);
	return (free_and_return(&split, ret));
}

static int		split_len(char **split)
{
	int	i;

	if (!split)
		return (0);
	i = 0;
	while (split[i])
		i++;
	return (i);
}

static void		trim_path(char **split)
{
	int		i;
	char	*path;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		path = ft_strtrim(split[i], " ");
		free(split[i]);
		split[i] = ft_strdup(path);
		free(path);
		i++;
	}
}

static int		pipe_loop(char **cmds, int nb_pipes, t_list **env_list)
{
	int		i;
	int		outputfd;
	pid_t	pid;
	int		pipefd[2];
	int		ret;

	i = 0;
	while (i < nb_pipes)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			close(pipefd[0]);
			if (i != 0)
				dup2(outputfd, STDIN_FILENO);
			if (nb_pipes != i + 1)
				dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			close(outputfd);
			exit(exec_cmd(cmds[i], env_list));
		}
		close(pipefd[1]);
		outputfd = dup(pipefd[0]);
		close(pipefd[0]);
		waitpid(pid, &ret, 0);
		ret = get_child_exit_status(ret);
		i++;
	}
	return (ret);
}

static int		exec_pipe(char *cmd, t_list **env_list)
{
	int		ret;
	char	**split;
	int		nb_pipes;

	if (ft_index(cmd, '|') < 0)
	{
		ret = exec_cmd(cmd, env_list);
		return (ret);
	}
	split = ft_split(cmd, '|');
	if (!(nb_pipes = split_len(split)))
		return (MALLOC_ERROR);
	trim_path(split);
	ret = pipe_loop(split, nb_pipes, env_list);
	free_str_arr(split);
	free(split);
	return (ret);
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
			ret = exec_pipe(tmp, env_list);
		free(tmp);
	}
	free_str_arr(commands);
	free(commands);
	return (ret);
}
