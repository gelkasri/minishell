/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:57:20 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/07 18:46:15 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <signal.h>

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
		path = (ft_index(split[0], '/') >= 0) ?
		check_path(NULL, split[0]) : NULL;
	if (path && !(id_child = fork()))
		sub_exec(path, split, get_env_array(env_list));
	ignore_signals();
	waitpid(id_child, &ret, 0);
	ret = get_child_exit_status(ret);
	if (!path)
		ret = handle_cmd_error(1, split[0]);
	free(path);
	return (free_and_return(&split, ret));
}

static void		child_exec(t_cmdlist *cmds, int *pipefd,
								int *child_fd, t_list **env_list)
{
	close(pipefd[0]);
	if (cmds->fd_in)
		child_fd[0] = get_last_fd(cmds->fd_in);
	if (child_fd[0] != -42)
	{
		dup2(child_fd[0], STDIN_FILENO);
		close(child_fd[0]);
	}
	child_fd[1] = (!(cmds->fd_out)) ? pipefd[1] :
		get_last_fd(cmds->fd_out);
	if (cmds->next || cmds->fd_out)
		dup2(child_fd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(child_fd[1]);
	if (cmds->fd_out_err)
	{
		dup2(get_last_fd(cmds->fd_out_err), STDERR_FILENO);
		close(get_last_fd(cmds->fd_out_err));
	}
	exit(exec_cmd(cmds->command, env_list));
}

static int		pipe_loop(t_cmdlist *cmds, t_list **env_list)
{
	int		child_fd[2];
	pid_t	pid[1024];
	int		pipefd[2];
	int		ret;
	int		i = 0;
	int		last;

	child_fd[0] = -42;
	while (cmds)
	{
		if (DEBUG)
			printf("command is : %s\n", cmds->command);
		pipe(pipefd);
		pid[i] = fork();
		if (pid[i] == 0)
			child_exec(cmds, pipefd, child_fd, env_list);
		close(pipefd[1]);
		child_fd[0] = dup(pipefd[0]);
		close(pipefd[0]);
		ret = get_child_exit_status(ret);
		cmds = cmds->next;
		i++;
	}
	last = i;
	while (--i)
		waitpid(pid[i - 1], &ret, 0);
	i = 0;
	return (ret);
}

static int		exec_pipe(char *cmd, t_list **env_list)
{
	int			ret;
	t_cmdlist	*commands;

	if (str_contains(cmd, "|<>") == -1)
	{
		ret = exec_cmd(cmd, env_list);
		return (ret);
	}
	commands = cmdparser(cmd);
	if (!commands)
		return (1);
	trim_path(commands);
	ret = pipe_loop(commands, env_list);
	cmdlist_clear(&commands, free);
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
		set_exit_status_var(ret, env_list);
	}
	free_str_arr(commands);
	free(commands);
	return (ret);
}
