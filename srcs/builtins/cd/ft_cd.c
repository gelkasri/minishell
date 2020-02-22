/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:59:39 by mle-moni          #+#    #+#             */
/*   Updated: 2020/02/21 22:07:42 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#define PATH_MAX 256

/*
** todo :
** - clean includes
*/

static char	*concat_paths(char *req_path, char *cwd_path)
{
	char	*final_path;
	int		final_path_len;

	final_path_len = 1 + ft_strlen(req_path) + ft_strlen(cwd_path);
	final_path = malloc(final_path_len);
	if (!final_path)
		return (0);
	ft_strcpy(final_path, cwd_path);
	ft_strcat(final_path, "/");
	ft_strcat(final_path, req_path);
	return (final_path);
}

static int	handle_error(int error_type, const char *req)
{
	if (error_type == 1)
		ft_putstr_fd("cd: error, malloc failed: ", 2);
	else if (error_type == 2)
		ft_putstr_fd("cd: too many arguments", 2);
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	if (error_type != 2)
		ft_putstr_fd(req, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

static int	change_directory(char *req_path, char *home_path, t_list **env_list)
{
	char	cwd_buffer[PATH_MAX];
	char	*final_path;
	int		ret;

	if (!getcwd(cwd_buffer, PATH_MAX))
		return (handle_error(0, req_path));
	if (!req_path)
		ret = chdir(home_path);
	else if (req_path[0] == '/')
		ret = chdir(req_path);
	else
	{
		final_path = concat_paths(req_path, cwd_buffer);
		if (!final_path)
			return (handle_error(1, req_path));
		ret = chdir(final_path);
		free(final_path);
	}
	if (!getcwd(cwd_buffer, PATH_MAX))
		return (handle_error(0, req_path));
	set_env_var("PWD", cwd_buffer, env_list);
	if (ret == -1)
		return (handle_error(0, req_path));
	return (0);
}

int			ft_cd(int ac, char **av, t_list **env_list)
{
	char *home_path;

	home_path = get_env_var("HOME", env_list);
	if (ac > 2)
		return (handle_error(2, ""));
	if (ac == 2)
		return (change_directory(av[1], home_path, env_list));
	else
		return (change_directory(0, home_path, env_list));
}

/*
** RETURN VALUES :
** 0 : OK
** 1 : an error occured
*/
