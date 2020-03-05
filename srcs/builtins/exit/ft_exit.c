/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-moni <mle-moni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 11:43:09 by mle-moni          #+#    #+#             */
/*   Updated: 2020/03/05 15:01:16 by gel-kasr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*
** SYNOPSIS
** exit [n]
** -
** DESCRIPTION
** Exit the shell.
** Exits the shell with a status of N.  If N is omitted, the exit status
** is that of the last command executed.
*/

static void	exit_error(const char *param, const char *err, int ret)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(param, 2);
	ft_putstr_fd(err, 2);
	exit(ret);
}

int			exit_body(int ac, char **av, t_list **env_list)
{
	char	*last_ret_str;
	int		last_ret;

	if (ac >= 2)
	{
		if (!ft_str_is_numeric(av[1]))
			exit_error(av[1], ": numeric argument required\n", 255);
	}
	if (ac > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (ac == 2)
		exit(ft_atoi(av[1]));
	last_ret_str = get_env_var("?", env_list);
	if (!last_ret_str)
	{
		ft_putstr_fd("exit: could not get env_var: $?\n", 2);
		return (1);
	}
	last_ret = ft_atoi(last_ret_str);
	free(last_ret_str);
	exit(last_ret);
}

int			ft_exit(int ac, char **av, t_list **env_list)
{
	char			*interactive;
	extern t_editor	**g_editor;

	interactive = get_env_var("INTERACTIVE", env_list);
	if (!(interactive && !ft_strcmp(interactive, "NO")))
	{
		ft_putendl("exit");
		if (g_editor && *g_editor)
			export_histo(*g_editor, env_list);
		free(interactive);
	}
	return (exit_body(ac, av, env_list));
}
