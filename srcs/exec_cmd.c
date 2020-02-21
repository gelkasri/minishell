/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gel-kasr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:57:20 by gel-kasr          #+#    #+#             */
/*   Updated: 2020/02/21 22:03:08 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*check_path(char *path, char *cmd, struct stat *buf)
{
	char	*join;
	char	*res;

	res = NULL;
	if (!(join = ft_strjoin3(path, "/", cmd)))
		return (NULL);
	if (lstat(join, buf) == 0)
		res = ft_strdup(join);
	free(join);
	return (res);
}

static char		*find_path(char *cmd, t_list **env_list)
{
	char		**split;
	int			i;
	char		*tmp;
	char		*res;
	struct stat	*buf;

	tmp = get_env_var("PATH", env_list);
	if (!(buf = malloc(sizeof(*buf))))
		return (NULL);
	if (!(split = ft_split(tmp, ':')))
		return (NULL);
	free(tmp);
	i = -1;
	res = NULL;
	while (split[++i] && !res)
		res = check_path(split[i], cmd, buf);
	free_str_arr(split);
	free(split);
	free(buf);
	return (res);
}

static int		exec_cmd(char *cmd, t_list **env_list)
{
	pid_t	id_child;
	int		ret;
	char	*path;
	char	**split;

	split = ft_split(cmd, ' ');
	ret = exec_builtins(split, env_list);
	if (ret >= 0)
		return (ret);
	path = find_path(split[0], env_list);
	if (path && !(id_child = fork()))
	{
		ret = execve(path, split, NULL);
		ft_printf("fail to execute command \"%s\"\n", path);
		exit(1);
	}
	wait(&id_child);
	if (!path)
		ft_printf("unknown command \"%s\"\n", cmd);
	free_str_arr(split);
	free(split);
	free(path);
	return (ret);
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
	return (1);
}
