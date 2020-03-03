/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:57:20 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/03/03 13:30:38 by mle-moni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>

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

static void		trim_path(t_cmdlist *commands)
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

/*
static int		set_write_fd(t_cmdlist *command, int defaultfd)
{
	t_cmdlist	*next;
	int			writefd;

	next = (t_cmdlist*)command->next;
	if (command->type == TO_FILE)
		writefd = open(next->command, O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR);
	else if (command->type == TO_FILE_APPEND)
		writefd = open(next->command, O_WRONLY | O_CREAT | O_APPEND,
		S_IRUSR | S_IWUSR);
	else
		writefd = defaultfd;
	if (writefd == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	return (writefd);
}
*/

static int		get_last_fd(t_fdlist *list)
{
	while (list && list->next)
		list = list->next;
	return (list->fd);
}

static int		pipe_loop(t_cmdlist* cmds, t_list **env_list)
{
	int		child_in;
	int		child_out;
	pid_t	pid;
	int		pipefd[2];
	int		ret;

	child_in = -42;
	while (cmds)
	{
		if (DEBUG)
			ft_printf("command is : %s\n", cmds->command);
		if (DEBUG)
		{
			cmds = cmds->next;
			ret = 0;
			continue ;
		}
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			close(pipefd[0]);
			if (cmds->fd_in)
				child_in = get_last_fd(cmds->fd_in);
			if (child_in != -42)
			{
				dup2(child_in, STDIN_FILENO);
				close(child_in);
			}
			child_out = (!(cmds->fd_out)) ? pipefd[1] : get_last_fd(cmds->fd_out);
			if (cmds->next)
				dup2(child_out, STDOUT_FILENO);
			close(pipefd[1]);
			close(child_out);
			if (cmds->fd_out_err)
				dup2(get_last_fd(cmds->fd_out_err), STDERR_FILENO);
			close(get_last_fd(cmds->fd_out_err));
			exit(exec_cmd(cmds->command, env_list));
		}
		close(pipefd[1]);
		child_in = dup(pipefd[0]);
		close(pipefd[0]);
		waitpid(pid, &ret, 0);
		ret = get_child_exit_status(ret);
		cmds = cmds->next;
	}
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
		return (MALLOC_ERROR);
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
	}
	free_str_arr(commands);
	free(commands);
	return (ret);
}
